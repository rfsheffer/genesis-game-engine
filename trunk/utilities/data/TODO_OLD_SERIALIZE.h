//
//  saverestore.h
//  Saves Entity datamaps to file. Restores datamaps from file.
//
//  Created by Ryan Sheffer on 17-07-10.
//  Copyright 2010 WorldScape Interactive. All rights reserved.
//

#ifndef SAVERESTORE_H
#define SAVERESTORE_H

#ifdef _WIN32
#pragma once
#endif

class game_world;

#define SAVE_FILE_HEADER	(('F'<<24)+('S'<<16)+('S'<<8)+'W')  // little-endian "WSSF" (Worldscape Save File)
#define SAVE_FILE_VERSION		1

// Save Types
#define ENTITY_SAVE		"entity"
#define ENGINE_SAVE		"engine"
#define RENDER_SAVE		"render"

/*
Objects are saved after a save_entity_header_t, and are just read byte by byte.
They look something like this:

struct obj
{
	short size_of_all;
	byte namesize; ( size = SAVE_NAME_HOLDER )
	char name[namesize];
	short type;
	short num_objs;
	obj data[sizeof(type)];
};
*/

struct restored_obj
{
	//short size_of_all;
	byte *namesize;
	char *name;
	short *type;
	short *num_objs;
	char *pdata;
};

// DO NOT CHANGE THIS!
#define SAVE_NAME_HOLDER		1

struct save_entity_header_t
{
	char entityname[MAX_ENTITY_NAME];
	char classname[MAX_CLASS_NAME];		// Classname.
	bool topclass;						// Is this the top most class in the class hierarchy?
	short num_objs;						// Number of Saved Objects.
};

// Gets written to the start of the file.
struct save_file_header_t
{
	int header;
	short version;
};

namespace save_restore
{
// ** SAVE **
	// Save World to File.
	bool SaveWorldToFile( game_world *pGameWorld );

	// Write Datamaps from class to buffer.
	void WriteDataMaps( void *pBaseClass, data_buffer *pData, datamap_t *dmap, string *ent_name );

	// Writes an Object to buffer.
	void WriteObject( void *pBaseClass, objdesc_t *pObject, data_buffer *pDataBuffer );

	void WriteTypeFromClass( void *pBaseClass, objdesc_t *pObject, char *pBuffer );

// ** RESTORE **
	// Restore World from File.
	bool RestoreWorldFromFile( int world_index );

	// Read entities from buffer, create entities, restore datamaps, handle custom case restores.
	void ReadSaveEntries( data_buffer *pDataBuffer, game_world *pGameWorld );

	int RestoreEntityObjects( char *pEntitySave, save_entity_header_t *pEntSaveHeader, baseentity *pEntity );
}

#endif