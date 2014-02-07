//
//  saverestore.cpp
//  Saves Entity datamaps to file. Restores datamaps from file.
//
//  Created by Ryan Sheffer on 17-07-10.
//  Copyright 2010 WorldScape Interactive. All rights reserved.
//

#include "saverestore.h"

// Note: Once the gamerules class is implemented, this should be removed.
const char save_folder[] = "save";
const char temp_game_name[] = "worldscape";
const char temp_account_name[] = "noname";

//===================================================================
// Purpose: Get Name for Save File.
//===================================================================
char *GetSaveFileName( int world_index, char *pName )
{
	if( !pName )
		return NULL;

	ws_snprintf( pName, MAX_PATH, "%s/%s_%s_save%d.wss", save_folder, temp_account_name, temp_game_name, world_index );
	return pName;
}

namespace save_restore
{
//***********************************************************************
// SAVE
//***********************************************************************

	//===================================================================
	// Purpose: Save World To File
	//===================================================================
	bool SaveWorldToFile( game_world *pGameWorld )
	{
		if( !pGameWorld || !g_pFileSystem )
			return false;

		// Create Header
		save_file_header_t SAVE_HEADER = { SAVE_FILE_HEADER, SAVE_FILE_VERSION };

		// Get File Name
		char Save_File_Name[MAX_PATH]; memset( Save_File_Name, 0, MAX_PATH );
		GetSaveFileName( pGameWorld->gameworld_index, &Save_File_Name[0] );

		// Open Writeable File
		FILE *pSave_File = NULL;
		if( g_pFileSystem->Open_File( &pSave_File, Save_File_Name, "wb", NULL ) )
			return false;

		size_t header_size = sizeof( SAVE_HEADER );
		if( header_size != fwrite( &SAVE_HEADER, 1, header_size, pSave_File ) )
		{
			g_pFileSystem->Close_File( pSave_File );
			return false;
		}

		// TODO: Write something to get a good estimate of how much to alloc.
		data_buffer *pBufferData = new data_buffer( 0, 128 );
		if( !pBufferData || pBufferData->GetError() )
		{
			g_pFileSystem->Close_File( pSave_File );
			return false;
		}

		pBufferData->SetBlockGrowth( 10 );

		// Buffer Save data from entities.
		for( int i = 0; i < pGameWorld->GetEntityCount(); i++ )
		{
			// TODO: There should be an entity save order for entity reliance.
			baseentity *pEntity = pGameWorld->GetEntity( i );
			if( pEntity )
			{
				// The entity chooses what it saves and doesnt save.
				pEntity->Save( pBufferData );
			}
		}

		// Now write the buffer to file
		if( pBufferData->m_iCurrent_Block )
		{
			// Write a header with some initial data.
			buffer_header_t buffer_header = { BUFFER_HEADER, BUFFER_FILE_VERSION, pBufferData->m_iCurrent_Block, pBufferData->m_iBufferSize };
			fwrite( &buffer_header, 1, sizeof( buffer_header ), pSave_File );

			// Write the data blocks
			fwrite( pBufferData->m_pBlocks, sizeof( data_block ), pBufferData->m_iCurrent_Block, pSave_File );

			// Write the buffer
			fwrite( pBufferData->m_pBaseData, 1, pBufferData->m_iCurrentPos, pSave_File );
		}

		// All Done! :)
		delete pBufferData;

		g_pFileSystem->Close_File( pSave_File );
		return true;
	}

	//===================================================================
	// Purpose: Write DataMaps to buffer.
	//===================================================================
	void WriteDataMaps( void *pBaseClass, data_buffer *pDataBuffer, datamap_t *dmap, string *ent_name )
	{
		if( !pBaseClass || !pDataBuffer || !dmap || !ent_name )
			return;

		pDataBuffer->StartWritting( ENTITY_SAVE ); // Write an entity save block.
		save_entity_header_t save_ent_header;
		bool first_class = true;

		datamap_t *pCurDataMap = dmap;
		while( pCurDataMap )
		{
			//Write entity save header first.
			strncpy( save_ent_header.entityname, ent_name->c_str(), MAX_ENTITY_NAME );
			strncpy( save_ent_header.classname, pCurDataMap->dataClassName, MAX_CLASS_NAME );
			save_ent_header.topclass = first_class;
			save_ent_header.num_objs = num_saved_obj( pCurDataMap );
			pDataBuffer->WriteBuffer( (char*)&save_ent_header, sizeof(save_ent_header) );

			// Some ents might not have any items.
			if( save_ent_header.num_objs )
			{
				// Write Objects
				for( int i = 0; i < pCurDataMap->NumObjs; i++ )
				{
					objdesc_t *pobject = &pCurDataMap->objList[i];
					WriteObject( pBaseClass, pobject, pDataBuffer );
				}
			}

			first_class = false;
			pCurDataMap = pCurDataMap->baseMap;
		}

		pDataBuffer->EndWritting();
	}

	void WriteObject( void *pBaseClass, objdesc_t *pObject, data_buffer *pDataBuffer )
	{
		if( !pBaseClass || !pObject || !pDataBuffer )
			return;

		// First determine the size of this obj_block
		int obj_name_len = strlen( pObject->objname );
		short obj_block_size = ( SHORT_SIZE + SAVE_NAME_HOLDER + obj_name_len + SHORT_SIZE + SHORT_SIZE + (GetObjectSize( pObject->objType ) * pObject->numobjs) );

		// Request a buffer
		char *pBuffer = pDataBuffer->CreateBuffer( obj_block_size );
		if( pBuffer )
		{
			// Size of this block of data.
			*((short*)pBuffer) = obj_block_size; pBuffer += SHORT_SIZE;
			// Name Length
			pBuffer[0] = (char)obj_name_len; pBuffer += 1;
			// Name
			memcpy( pBuffer, pObject->objname, obj_name_len ); pBuffer += obj_name_len;
			// Type
			*((short*)pBuffer) = pObject->objType; pBuffer += SHORT_SIZE;
			// num items
			*((short*)pBuffer) = pObject->numobjs; pBuffer += SHORT_SIZE;

			// Objects
			WriteTypeFromClass( pBaseClass, pObject, pBuffer );
		}
	}

	void WriteTypeFromClass( void *pBaseClass, objdesc_t *pObject, char *pBuffer )
	{
		if( !pBaseClass || !pObject || !pBuffer )
			return;

		int objectsize = GetObjectSize( pObject->objType );

		for( int i = 0; i < pObject->numobjs; i++ )
		{
			// Get pointer to REAL object so we can copy it.
			char *pVar = ((char *)pBaseClass + pObject->objoffset + ( objectsize * i ));
			memcpy( pBuffer, pVar, objectsize ); pBuffer += objectsize;
		}
	}

//***********************************************************************
// RESTORE
//***********************************************************************

	//===================================================================
	// Purpose: Load World from File.
	//===================================================================
	bool RestoreWorldFromFile( int world_index )
	{
		// The world needs to be clear before it can be restored.
		if( !g_game_world || g_game_world->GetEntityCount() )
			return false;

		char Save_File_Name[MAX_PATH]; memset( Save_File_Name, 0, MAX_PATH );
		GetSaveFileName( world_index, &Save_File_Name[0] );

		// Open Save File
		FILE *pSave_File = NULL;
		long Save_File_Len = 0;
		if( g_pFileSystem->Open_File( &pSave_File, Save_File_Name, "rb", &Save_File_Len ) )
			return false;

		// Read the Header Data.
		save_file_header_t save_header;
		size_t save_header_size = sizeof( save_header );
		if( save_header_size != fread( &save_header, 1, save_header_size, pSave_File ) )
		{
			g_pFileSystem->Close_File( pSave_File );
			return false;
		}

		// Check Save File Version
		if( (save_header.header != SAVE_FILE_HEADER) || (save_header.version != SAVE_FILE_VERSION) )
		{
			g_pFileSystem->Close_File( pSave_File );
			return false;
		}

		// Read the data buffer header.
		buffer_header_t buffer_header;
		size_t buffer_header_size = sizeof( buffer_header );
		if( buffer_header_size != fread( &buffer_header, 1, buffer_header_size, pSave_File ) )
		{
			g_pFileSystem->Close_File( pSave_File );
			return false;
		}

		if( (buffer_header.id != BUFFER_HEADER) || (buffer_header.version != BUFFER_FILE_VERSION) )
		{
			g_pFileSystem->Close_File( pSave_File );
			return false;
		}

		// Save buffer map and buffer itself to a data_buffer.
		data_buffer *pBufferData = new data_buffer( buffer_header.BufferSize, buffer_header.Num_Blocks );
		if( !pBufferData || pBufferData->GetError() )
		{
			g_pFileSystem->Close_File( pSave_File );
			return false;
		}

		// Read blocks
		int blocks_size = (sizeof( data_block ) * buffer_header.Num_Blocks );
		if( blocks_size != fread( pBufferData->m_pBlocks, 1, blocks_size, pSave_File ) )
		{
			g_pFileSystem->Close_File( pSave_File );
			return false;
		}

		// Read Buffer
		if( buffer_header.BufferSize != fread( pBufferData->m_pBaseData, 1, buffer_header.BufferSize, pSave_File ) )
		{
			g_pFileSystem->Close_File( pSave_File );
			return false;
		}

		ReadSaveEntries( pBufferData, g_game_world );

		delete pBufferData;

		g_pFileSystem->Close_File( pSave_File );
		return true;
	}

	void ReadSaveEntries( data_buffer *pDataBuffer, game_world *pGameWorld )
	{
		if( !pDataBuffer || !pGameWorld ) 
			return;

		int save_header_size = sizeof( save_entity_header_t );
		int num_bytes_read;
		int num_obj_bytes_read;

		// Iterate the blocks, restore entities.
		for( int i = 0; i < pDataBuffer->m_iNum_Blocks; i++ )
		{
			data_block *pCurBlock = &pDataBuffer->m_pBlocks[i];
			if( !pCurBlock )
				continue;

			// Is this an ent?
			if( ws_strncmp( pCurBlock->name, ENTITY_SAVE, MAX_DATA_BLOCK_NAME ) != 0 )
				continue;

			if( !pDataBuffer->SetBufferPos( pCurBlock->offset ) )
				continue;

			baseentity *pEntity = NULL;

			num_bytes_read = 0; // We will use this to determine when we are at the end.
			char *pEntitySave = pDataBuffer->m_pCurrentData; // Pointer to were we will start reading from.

			while( num_bytes_read < pCurBlock->size )
			{
				save_entity_header_t *pEntSaveHeader = (save_entity_header_t *)pEntitySave;
				num_bytes_read += save_header_size;
				pEntitySave += save_header_size;

				// Create Ent if topclass.
				if( pEntSaveHeader->topclass )
				{
					pEntity = CreateEntityByName( pEntSaveHeader->entityname );
					if( !pEntity )
					{
						// Warning Message.
						WarningFmtMsg( "Restore : Creating unknown Entity %s", pEntSaveHeader->entityname );
						break;
					}
				}

				// Restore Class Data.
				if( pEntSaveHeader->num_objs )
				{
					num_obj_bytes_read = RestoreEntityObjects( pEntitySave, pEntSaveHeader, pEntity );
					if( num_obj_bytes_read == 0 )
						break;

					num_bytes_read += num_obj_bytes_read;
					pEntitySave += num_obj_bytes_read;
				}
			}

			assert( (num_bytes_read == pCurBlock->size) );
			if( num_bytes_read != pCurBlock->size )
			{
				// Warning!
				WarningMsg( "Restore : num_bytes_read != pCurBlock->size !!" );
			}

			// If Entity was restored, spawn it.
			if( pEntity )
			{
				// Let ents do some pre stuff
				pEntity->Restore( pDataBuffer );

				// Spawn Ent into World.
				if( pGameWorld->SpawnIntoWorld( pEntity ) == BAD_ENT_INDEX )
				{
					delete pEntity;
					pEntity = NULL;
				}
			}
		}
	}

	int RestoreEntityObjects( char *pEntitySave, save_entity_header_t *pEntSaveHeader, baseentity *pEntity )
	{
		if( !pEntitySave || !pEntSaveHeader || !pEntity )
			return 0;

		char *pObjectData = pEntitySave;
		int num_bytes_read = 0;

		restored_obj ent_obj;

		for( int i = 0; i < pEntSaveHeader->num_objs; i++ )
		{
			// Prepare a holder for the current object.
			short *obj_size = (short *)pObjectData; pObjectData += SHORT_SIZE;
			ent_obj.namesize = (byte *)pObjectData; pObjectData += SAVE_NAME_HOLDER;
			ent_obj.name = pObjectData; pObjectData += *ent_obj.namesize;
			ent_obj.type = (short *)pObjectData; pObjectData += SHORT_SIZE;
			ent_obj.num_objs = (short *)pObjectData; pObjectData += SHORT_SIZE;

			// Restore Data to pEntity

			int objectsize = GetObjectSize( *ent_obj.type );

			// Find Entry in entity datamap.
			datamap_t *pcurmap = pEntity->GetDataMap();
			while( pcurmap != NULL )
			{
				// Find the right class.
				if( !ws_strncmp( pcurmap->dataClassName, pEntSaveHeader->classname, MAX_CLASS_NAME ) )
				{
					// Find the entry
					for( int cur_obj = 0; cur_obj < pcurmap->NumObjs; cur_obj++ )
					{
						objdesc_t *pObject = &pcurmap->objList[cur_obj];
						if( strlen( pObject->objname ) == *ent_obj.namesize )
						{
							// Compare names, is this the object we want?
							if( !ws_strncmp( pObject->objname, ent_obj.name, *ent_obj.namesize ) )
							{
								for( int j = 0; j < pObject->numobjs; j++ )
								{
									// Get pointer to REAL object so we can restore to it.
									char *pVar = ((char *)pEntity + pObject->objoffset + ( objectsize * j ));
									memcpy( pVar, pObjectData, objectsize ); pObjectData += objectsize;
								}
								break;
							}
						}
					}
					break;
				}

				pcurmap = pcurmap->baseMap;
			}

			// next!
			num_bytes_read += *obj_size;
		}

		return num_bytes_read;
	}
}