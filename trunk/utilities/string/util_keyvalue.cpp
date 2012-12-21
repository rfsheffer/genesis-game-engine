//========= Copyright © 2012-2013, Ryan Sheffers Game Utility Library ==============================//
//
// Purpose: Parses scripts with keyvalue based syntax.
//
//==================================================================================================//

#include "allhead.h"
#include "util_keyvalue.h"
#include <string>

using namespace std;

//===================================================================
// Purpose: Determine what the character means to this keyvalues file.
//===================================================================

enum key_defines
{
	LEFT_BRACKET,	// { 123
	RIGHT_BRACKET,	// } 125
	DOUBLE_QUOTE,	// " 34
	SPACEBAR,		// 32
	USABLE_CHAR,	// Just a char we should use.
	FSLASH_CHAR,	// For detecting comments.
	IGNORE_CHAR		// A bunch of ascii characters that will be ignored. ( http://www.asciitable.com/ anything below 32 )
};

char DecipherChar( char character )
{
	if ( character == '{' )		// 123
		return LEFT_BRACKET;

	if ( character == '}' )		// 125
		return RIGHT_BRACKET;

	if ( character == '"' )		// 34
		return DOUBLE_QUOTE;

	if ( character == 32 )
		return SPACEBAR;

	if ( character == '/' )
		return FSLASH_CHAR;

	if ( character < 32 )
		return IGNORE_CHAR;
	else
		return USABLE_CHAR;
}

//===================================================================
// Purpose: Alert the console of a syntax error.
//===================================================================
void KeyvaluesSyntaxError( char *pErrorText )
{
	printf( "Keyvalues syntax Error!, %s!\n", pErrorText );
	//WarningFmtMsg( "Keyvalues syntax Error : %s!\n", pErrorText );
}

// ParseScript commands. 
enum kv_commands
{
	KV_IGNORE,
	KV_ADD_CHAR,
	KV_APPEND_CHAR,
	KV_NEW_KEYVALUE,
	KV_KILL
};

//===================================================================
// Purpose: Parse a text file script of buffer.
// How To: Pass in a pointer to a keyvalue buffer of filename, if the return bool is true, there is a syntax error and the keyvalue was not created.
//===================================================================
bool ParseKVScript( const char *szScriptName, int stringsize, keyvalue **pReturnKV, bool isfile )
{
	//=====================================================
	// PROCESS FILE, GET IT READY FOR PARSE.
	//=====================================================
	if ( szScriptName == NULL || strlen(szScriptName) == 0 )
		return TRUE;

	long cur_position = 0;	// Byte Position
	char cur_c;	// Current char

	FILE *pKV_File = NULL;	// File pointer
	long buffersize = 0;		// File size in Bytes

	char *pFileBuffer = NULL;
	const char *pKeyvalueBuffer = NULL;

	if( isfile )
	{
		// Open KV file
		if( fopen_s( &pKV_File, szScriptName, "rb") )
			return TRUE;

		fseek(pKV_File, 0, SEEK_END);
		buffersize = ftell(pKV_File);
		rewind(pKV_File);

		// Buffer KV file
		pFileBuffer = new char[buffersize];
		if( buffersize != fread ( pFileBuffer, 1, buffersize, pKV_File ) )
		{
			fclose( pKV_File );
			delete [] pFileBuffer;
			return TRUE;
		}

		// We can close this now that it is buffered into memory.
		fclose( pKV_File );
		pKV_File = NULL;

		pKeyvalueBuffer = pFileBuffer;
	}
	else
	{
		pKeyvalueBuffer = szScriptName;
		buffersize = stringsize;
	}

	bool bad_syntax = FALSE;

	// These will turn on and off as quotes open and close while we parse the file. They will also be used to determine syntax errors.
	bool quote_open = FALSE;
	bool char_with_no_quote = FALSE;

	// Hacky little addon to allow commented lines.
	int comment_open = 0; // 0 = no, 1 = waiting for next slash, 2 = line is commented out.

	string keyvalue_char;

	int kv_command = 0;	// command the switch will give.

	keyvalue *pCurKeyvalue = NULL;

	// skidz: Valve keyvalues have roots.
	// Create the parent keyvalue.
	keyvalue *pMainRoot = new keyvalue;

	pMainRoot->SetName("kvroot");
	pMainRoot->pKVParent = NULL;

	pCurKeyvalue = new keyvalue;
	pCurKeyvalue->pKVParent = pMainRoot;

	pMainRoot->pKeyValues[0] = pCurKeyvalue;


	//=====================================================
	// MAIN PARSE LOOP
	//=====================================================
	while( cur_position < buffersize ) // While we aren't at the end of the buffer.
	{
		cur_c = pKeyvalueBuffer[cur_position];

		// Check if we are ignoring an entire line! Ignores characters to the next return character.
		if ( comment_open == 2 )
		{
			if ( cur_c == 10 ) // 10 is a newline ascii character.
			{
				comment_open = 0;
			}
			else
			{
				cur_position++;
				continue;
			}
		}

		//=====================================================
		// DECIPHERE CHAR
		//=====================================================
		switch( DecipherChar( cur_c ) )
		{
			case LEFT_BRACKET: // {
				{
					if ( quote_open )
					{
						KeyvaluesSyntaxError((char*)"Quotation mark and bracket mixup detected");
						bad_syntax = TRUE;
						kv_command = KV_KILL;
						break;
					}

					if ( pCurKeyvalue->bracket_open )
					{
						KeyvaluesSyntaxError( (char*)"Double Bracket detected" );
						bad_syntax = TRUE;
						kv_command = KV_KILL;
						break;
					}

					if ( pCurKeyvalue->value != NULL )
					{
						KeyvaluesSyntaxError( (char*)"Trying to create a node keyvalue with a value based keyvalue ");
						bad_syntax = TRUE;
						kv_command = KV_KILL;
						break;
					}

					if ( pCurKeyvalue->name == NULL )
					{
						KeyvaluesSyntaxError( (char*)"Trying to create a sub set of keyvalues without a reference name" );
						bad_syntax = TRUE;
						kv_command = KV_KILL;
						break;
					}

					// Set current keyvalue as node, create a new keyvalue.
					pCurKeyvalue->bracket_open = TRUE;
					pCurKeyvalue->node = TRUE;
					kv_command = KV_NEW_KEYVALUE;
					break;
				}

			case RIGHT_BRACKET:  // }
				{
					// If we hit this that means we are at the end of the parents block and it must be shutdown and forgotten.
					if ( quote_open )
					{
						KeyvaluesSyntaxError( (char*)"Quotation mark and bracket mixup detected" );
						bad_syntax = TRUE;
						kv_command = KV_KILL;
						break;
					}

					if ( !pCurKeyvalue->pKVParent )
					{
						KeyvaluesSyntaxError( (char*)"End bracket with no owner" );
						bad_syntax = TRUE;
						kv_command = KV_KILL;
						break;
					}

					// Set back to parent, its subset is ending.
					pCurKeyvalue = pCurKeyvalue->pKVParent;

					if ( !pCurKeyvalue->bracket_open )
					{
						KeyvaluesSyntaxError( (char*)"End bracket with no starting bracket" );
						bad_syntax = TRUE;
						kv_command = KV_KILL;
						break;
					}

					pCurKeyvalue->bracket_open = FALSE;

					// Check for any loose keyvalues that didnt get assigned.
					for( int i = 0; i < MAX_SUB_KEYVALUES; i++ )
					{
						if ( pCurKeyvalue->pKeyValues[i] != NULL )
						{
							if ( pCurKeyvalue->pKeyValues[i]->name == NULL )
							{
								delete pCurKeyvalue->pKeyValues[i];
								pCurKeyvalue->pKeyValues[i] = NULL;
							}
						}
					}
					
					if ( pCurKeyvalue->pKVParent == NULL )
					{
						KeyvaluesSyntaxError( (char*)"Parent reached as NULL" );
						kv_command = KV_KILL;
						break;
					}
					else
					{
						// Backtrack to parent, and create its next keyvalue.
						pCurKeyvalue = pCurKeyvalue->pKVParent;

						// Create a new keyvalue, set its parent.
						keyvalue *pNewKV = new keyvalue;

						// Add new keyvalue to parents list.
						for( int i = 0; i < MAX_SUB_KEYVALUES; i++ )
						{
							if ( pCurKeyvalue->pKeyValues[i] == NULL )
							{
								pCurKeyvalue->pKeyValues[i] = pNewKV;
								break;
							}
						}
						// Set new keyvalues parent.
						pNewKV->pKVParent = pCurKeyvalue;

						// Set the new keyvalue as current.
						pCurKeyvalue = NULL;
						pCurKeyvalue = pNewKV;

						kv_command = KV_IGNORE;
						break;
					}
					break;
				}

			case DOUBLE_QUOTE:
				{
					// If no brackets are open, this is most likely a parent node.
					if ( quote_open )
					{
						quote_open = FALSE;

						// We are done recieving the char, create the char data and assign it to this keyvalue.
						if ( keyvalue_char.size() != 0 )
						{
							kv_command = KV_APPEND_CHAR;
						}
						else
						{
							/*KeyvaluesSyntaxError( "Open and closing quotes with no substance" );
							bad_syntax = TRUE;
							kv_command = KV_KILL;*/

							//Note: This was changed by request, keyvalues can have no content within the quotes.
							keyvalue_char.append(1, '0');
							kv_command = KV_APPEND_CHAR;
						}
						break;
					}
					else if ( !quote_open )
					{
						quote_open = TRUE;
						kv_command = KV_IGNORE;
						break;
					}
					break;
				}

			case SPACEBAR:
				{
					// If there are quotes, spaces are included
					if ( quote_open )
					{
						// add char
						kv_command = KV_ADD_CHAR;
						break;
					}

					// Else ignore spacebar.
					kv_command = KV_IGNORE;
					break;
				}

			case FSLASH_CHAR:
				{
					// We need to determine if a line is ignored. Comments don't work within quotes.
					if ( (comment_open == 1) && !quote_open )
					{
						// kill the current line.
						char_with_no_quote = FALSE;

						// BUG: this will scrap the last string, which could have been a subkey. :(
						// I will fix it if it becomes a problem.
						if( keyvalue_char.size() != 0 )
						{
							//KeyvaluesSyntaxError( (char*)"Scrapping subkey because of comment, show to Ryan!" );
							keyvalue_char.clear();
						}

						comment_open = 2;

						kv_command = KV_IGNORE;
						break;
					}

					if ( !quote_open )
					{
						// We don't have an open quote, tell the command processing plant to watch out for the end of this.
						char_with_no_quote = TRUE;
					}

					// add char
					kv_command = KV_ADD_CHAR;

					// set comment flag.
					if ( comment_open == 0 )
						comment_open = 1;

					break;
				}

			case IGNORE_CHAR:
				{
					kv_command = KV_IGNORE;
					break; // go to next char.
				}

			case USABLE_CHAR:
				{
					if ( !quote_open )
					{
						// We don't have an open quote, tell the command processing plant to watch out for the end of this.
						char_with_no_quote = TRUE;
					}

					// Just in case this is open because of a previous slash.
					comment_open = 0;

					// add char
					kv_command = KV_ADD_CHAR;
					break;
				}
		}

		//=====================================================
		// KEYVALUE COMMAND PROCESSING PLANT
		//=====================================================
		if ( kv_command == KV_IGNORE ) //**************
		{
			// Special case handling here.

			// If the user didn't use quotes to contain a set of characters, determine the end here.
			if ( char_with_no_quote )
			{
				// Any ignored char will cause an append of the current char.
				kv_command = KV_APPEND_CHAR;
				char_with_no_quote = FALSE;
			}
		}

		if ( kv_command == KV_ADD_CHAR ) //**************
		{
			keyvalue_char.append(1, cur_c);
		}
		else if ( kv_command == KV_APPEND_CHAR ) //**************
		{
			// Just in case this is open because of a previous slash.
			comment_open = 0;

			char *ToSlot = (char*)malloc(keyvalue_char.size()+1);
			if ( !ToSlot )
			{
				KeyvaluesSyntaxError( (char*)"OUT OF MEMORY" );
				bad_syntax = TRUE;
				break;
			}

			strncpy_s( ToSlot, keyvalue_char.size() + 1, keyvalue_char.c_str(), keyvalue_char.size() );
			ToSlot[keyvalue_char.size()] = '\0';

			// Assign the name for the keyvalue
			if ( pCurKeyvalue->name == NULL )
			{
				pCurKeyvalue->name = ToSlot;
			}
			else
			{
				// We are a sub keyvalue with only a value, backtrack to parent, and create its next keyvalue.
				pCurKeyvalue->value = ToSlot;
				pCurKeyvalue = pCurKeyvalue->pKVParent;

				// Create a new keyvalue, set its parent.
				keyvalue *pNewKV = new keyvalue;

				// Add keyvalue to parents list.
				int i = 0;
				for( ; i < MAX_SUB_KEYVALUES; i++ )
				{
					if ( pCurKeyvalue->pKeyValues[i] == NULL )
					{
						pCurKeyvalue->pKeyValues[i] = pNewKV;
						break;
					}
				}
				// If we maxed out, this is an error.
				if( i == MAX_SUB_KEYVALUES )
				{
					delete pNewKV;
					KeyvaluesSyntaxError( (char*)"Maximum sub keyvalues reached!" );
					bad_syntax = TRUE;
					break;
				}
				// Set new keyvalues parent.
				pNewKV->pKVParent = pCurKeyvalue;

				// Set the new keyvalue as current.
				pCurKeyvalue = NULL;
				pCurKeyvalue = pNewKV;
			}

			// Reset current char.
			ToSlot = NULL;
			keyvalue_char.clear();
		}
		else if ( kv_command == KV_NEW_KEYVALUE ) //**************
		{
			// Create a new keyvalue, set its parent.
			keyvalue *pNewKV = new keyvalue;

			// Add keyvalue to parents list.
			for( int i = 0; i < MAX_SUB_KEYVALUES; i++ )
			{
				if ( pCurKeyvalue->pKeyValues[i] == NULL )
				{
					pCurKeyvalue->pKeyValues[i] = pNewKV;
					break;
				}
			}
			// Set new keyvalues parent.
			pNewKV->pKVParent = pCurKeyvalue;

			// Set the new keyvalue as current.
			pCurKeyvalue = NULL;
			pCurKeyvalue = pNewKV;
		}
		else if ( kv_command == KV_KILL ) //**************
		{
			break;
		}
		
		kv_command = 0;
		cur_position++;
	}

	if( pFileBuffer )
		delete [] pFileBuffer;

	// Destory KV data if syntax errors exist.
	if ( bad_syntax )
	{
		delete pCurKeyvalue;
	}
	else
	{
		// some last minute checks here.
		while ( pCurKeyvalue != NULL )
		{
			// check for unused values.
			for( int i = 0; i < MAX_SUB_KEYVALUES; i++ )
			{
				if ( pCurKeyvalue->pKeyValues[i] != NULL )
				{
					if ( pCurKeyvalue->pKeyValues[i]->name == NULL )
					{
						delete pCurKeyvalue->pKeyValues[i];
						pCurKeyvalue->pKeyValues[i] = NULL;
					}
				}
			}

			if ( pCurKeyvalue->pKVParent )
				pCurKeyvalue = pCurKeyvalue->pKVParent;
			else
			{
				*pReturnKV = pCurKeyvalue;
				return bad_syntax;
			}
		}
		*pReturnKV = pCurKeyvalue;
	}

	if(pKV_File)
	{
		fclose(pKV_File);
	}

	return bad_syntax;
}

// Common keys we need to use in the creation of KV files.
#define	KV_TAB		9
#define	KV_NL		10
#define	KV_RETURN	13
#define KV_QUOTE	34

//===================================================================
// Purpose: Adds a name in quotes to the end of a file.
//===================================================================
void AddNametoFile( char *szName, FILE *pFile )
{
	if ( szName && pFile )
	{
		char quote[2];

		quote[0] = KV_QUOTE;
		quote[1] = 0;

		fputs ( quote, pFile);
		fputs ( szName, pFile);
		fputs ( quote, pFile);
	}
}

//===================================================================
// Purpose: Adds special characters to the end of a file.
//===================================================================
void AddStructuretoFile( FILE *pFile, bool b_return, bool b_tab, bool l_bracket, bool r_bracket, int level )
{
	if ( pFile )
	{
		// Newline
		if ( b_return )
		{
			char szreturn[3];

			szreturn[0] = KV_RETURN;
			szreturn[1] = KV_NL;
			szreturn[2] = 0;

			fputs ( szreturn, pFile);
		}
		// Tab
		if ( b_tab )
		{
			for ( int i = 0; i < level; i++ )
			{
				char sztab[2];

				sztab[0] = KV_TAB;
				sztab[1] = 0;

				fputs ( sztab, pFile);
			}
		}
		// L Brackets
		if ( l_bracket )
		{
			char szl_bracket[2];

			szl_bracket[0] = '{';
			szl_bracket[1] = 0;

			fputs ( szl_bracket, pFile);
		}
		// R Brackets
		if ( r_bracket )
		{
			char szr_bracket[2];

			szr_bracket[0] = '}';
			szr_bracket[1] = 0;

			fputs ( szr_bracket, pFile);
		}

	}
}

//===================================================================
// Purpose: Writes a keyvalues subset to file, only CreateKVScript should call this.
//===================================================================
void WriteSubSet( keyvalue *pWriteKV, FILE *pFile, int i_level )
{
	int level = i_level;

	if ( !pWriteKV || !pWriteKV->node || !pFile )
		return;

	AddStructuretoFile( pFile, true, true, false, false, i_level ); // Move into place.
	AddNametoFile( pWriteKV->name, pFile ); // name

	AddStructuretoFile( pFile, true, true, true, false, i_level ); // left bracket

	// to next level!
	level++;

	// Handel root, subsets handel themselves with WriteSubSet.
	for(int i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pWriteKV->pKeyValues[i] != NULL )
		{
			if ( pWriteKV->pKeyValues[i]->node )
			{
				WriteSubSet( pWriteKV->pKeyValues[i], pFile, level ); // RECURSION LAWL
				continue;
			}
			if ( pWriteKV->pKeyValues[i]->value )
			{
				// move into place.
				AddStructuretoFile( pFile, true, true, false, false, level );
				AddNametoFile( pWriteKV->pKeyValues[i]->name, pFile );
				fputs ( " ", pFile);
				AddNametoFile( pWriteKV->pKeyValues[i]->value, pFile );
			}
		}
	}

	// All Done!
	AddStructuretoFile( pFile, true, true, false, true, i_level );
}

//===================================================================
// Purpose: Create Keyvalues File
//===================================================================
bool CreateKVScript( char *szScriptName, keyvalue *pWriteKV )
{
	// Both must exist.
	if ( !pWriteKV || !szScriptName )
		return FALSE;

	// If it exists but there is no valid data to write.
	if ( pWriteKV->name == NULL )
		return FALSE;

	// File pointer
	FILE *pFile = NULL;
	int err = fopen_s( &pFile, szScriptName, "wb");

	// File Read Error.
	if (err != 0) 
	{
		return FALSE;
	}

	int level = 0;

	// Add header.
	fputs ( "// Copyright © 2012, Interdimensional Games Incorporated, All rights reserved. \n// Auto-Generated Keyvalue Script", pFile);
	AddStructuretoFile( pFile, true, false, false, false, level );

	// The first thing we do is add the name, then we loop through every element there after.
	// skidz: Keyvalues no longer need a main parent, the first kv is always the root, dont write it.
	//AddNametoFile( pWriteKV->name, pFile );
	//AddStructuretoFile( pFile, true, false, true, false, level );

	// Handel root, subsets handle themselves with WriteSubSet.
	for(int i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pWriteKV->pKeyValues[i] != NULL )
		{
			if ( pWriteKV->pKeyValues[i]->node )
			{
				WriteSubSet( pWriteKV->pKeyValues[i], pFile, level );
				continue;
			}
			if ( pWriteKV->pKeyValues[i]->value )
			{
				// move into place.
				AddStructuretoFile( pFile, true, true, false, false, level );
				AddNametoFile( pWriteKV->pKeyValues[i]->name, pFile );
				fputs ( " ", pFile);
				AddNametoFile( pWriteKV->pKeyValues[i]->value, pFile );
			}
		}
	}

	// All Done!
	//AddStructuretoFile( pFile, true, false, false, true, level );

	fclose (pFile);

	return TRUE;
}

//===================================================================
// Purpose: Creates a brand new kv block, add kv nodes and kv values to it.
//===================================================================
keyvalue *CreateNewKVBlock( char *szBlockName )
{
	if (!szBlockName)
		return NULL;

	keyvalue *pNewKVBlock = new keyvalue;
	if ( pNewKVBlock )
	{
		pNewKVBlock->SetName( szBlockName );
		pNewKVBlock->node = true;
		return pNewKVBlock;
	}
	return NULL;
}

//===================================================================
// Purpose: Creates a new kv node for a parent, add kv nodes and kv values to it.
//===================================================================
keyvalue *CreateNewKVNode( char *szNodeName, keyvalue *pParent )
{
	if (!szNodeName || !pParent )
		return NULL;
	
	keyvalue **pParentIndex = NULL;

	int i;
	for( i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pParent->pKeyValues[i] == NULL )
		{
			pParentIndex = &pParent->pKeyValues[i];
			break;
		}
	}

	if ( i >= MAX_SUB_KEYVALUES )
		return NULL;

	keyvalue *pNewKVNode = new keyvalue;
	if ( pNewKVNode )
	{
		pParent->node = true;
		pNewKVNode->SetName( szNodeName );
		pNewKVNode->node = true;
		*pParentIndex = pNewKVNode;
		return pNewKVNode;
	}
	return NULL;
}

//===================================================================
// Purpose: Creates a new kv value for a node.
//===================================================================
bool CreateNewKVValue( const char *szName, const char *szValue, keyvalue *pNode )
{
	if (!szName || !szValue || !pNode )
		return FALSE;

	keyvalue **pParentIndex = NULL;

	int i;
	for( i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pNode->pKeyValues[i] == NULL )
		{
			pParentIndex = &pNode->pKeyValues[i];
			break;
		}
	}

	if ( i >= MAX_SUB_KEYVALUES )
		return FALSE;

	keyvalue *pNewKVNode = new keyvalue;
	if ( pNewKVNode )
	{
		pNewKVNode->SetName( szName );
		pNewKVNode->SetValue( szValue );
		*pParentIndex = pNewKVNode;
		return TRUE;
	}
	return FALSE;
}

//*******************************************************************
// Keyvalue Functions
//*******************************************************************

//===================================================================
// Purpose: Find keyvalue by name, create new if none is found. ( Only creates new if bCreate is set to true )
//===================================================================
keyvalue *keyvalue::FindKey( const char *szKeyName, bool bCreate )
{
	// Search all keyvalues for a keyvalue named szKeyName.
	for(int i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pKeyValues[i] != NULL )
		{
			if ( _strnicmp( pKeyValues[i]->name, szKeyName, strlen( szKeyName ) ) == 0 )
			{
				// If key was found, return it.
				return pKeyValues[i];
			}

			/*if ( pKeyValues[i]->node )
			{
				// Search all child keyvalues as well.
				keyvalue *psubkey = pKeyValues[i]->FindKey( szKeyName, false );
				if ( psubkey )
					return psubkey;
				else
					continue;
			}*/
		}
	}
	// Nothing was found, create new sub key if requested.
	if ( bCreate )
	{
		for(int i = 0; i < MAX_SUB_KEYVALUES; i++ )
		{
			if ( pKeyValues[i] == NULL )
			{
				pKeyValues[i] = new keyvalue;
				if ( pKeyValues[i] )
				{
					pKeyValues[i]->SetName(szKeyName);
					return pKeyValues[i];
				}
				else
				{
					assert( pKeyValues[i] ); // Not enough memory?
					return NULL;
				}
			}
		}
	}

	return NULL;
}

//===================================================================
// Purpose: Gets the next keyvalue in line on the level pCurrentKey is on.
//===================================================================
keyvalue *keyvalue::GetNextKey( keyvalue *pCurrentKey )
{
	// If pCurrentKey is NULL, get first key.
	if ( pCurrentKey == NULL )
	{
		if ( pKeyValues[0] )
			return pKeyValues[0];
		else
			return NULL;
	}

	// If pCurrentKey, then look for pCurrentKey, get the next value after that.
	for( int i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pKeyValues[i] ) // If keyvalues can be removed, this needs to be redone.
		{
			if ( pKeyValues[i] == pCurrentKey )
			{
				if ( pKeyValues[i+1] )
					return pKeyValues[i+1];
				else
					return NULL;
			}
		}
	}

	return NULL;
}

//===================================================================
// Purpose: Gets the next keyvalue in line on the level pCurrentKey is on, but has to be the same name as pCurrentKey
//===================================================================
/*keyvalue *keyvalue::GetNextKeyByName( keyvalue *pCurrentKey )
{
	// If pCurrentKey is NULL, get first key.
	if ( pCurrentKey == NULL || pCurrentKey->name == NULL )
	{
		return NULL;
	}

	// If pCurrentKey, then look for pCurrentKey, get the next value after that.
	for( int i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pKeyValues[i] ) // If keyvalues can be removed, this needs to be redone.
		{
			if ( pKeyValues[i] == pCurrentKey )
			{
				keyvalue *pNextKey = pKeyValues[i+1];
				if ( pNextKey && pNextKey->name )
				{
					if( !ws_strnicmp( pNextKey->name, pCurrentKey->name, strlen( pCurrentKey->name ) ) )
						return pNextKey;
				}
				else
					return NULL;
			}
		}
	}

	return NULL;
}*/

//===================================================================
// Purpose: Sets the keyvalues name
//===================================================================
void keyvalue::SetName( const char *szKeyName )
{
	if ( !szKeyName )
		return;

	int stringsize = strlen( szKeyName );
	char *ToName = (char*)malloc(stringsize+1);
	if ( !ToName )
	{
		assert( !ToName ); // out of memory.
	}

	// Null out new data.
	memset( ToName, 0, (stringsize+1) );

	// Set ToName to szKeyName.
	strncpy_s( ToName, stringsize + 1, szKeyName, stringsize );

	// just in case.
	ToName[stringsize] = '\0';

	// If we already have a name, free the memory its using.
	if ( name )
		free( name );

	name = NULL;
	name = ToName;
}

//===================================================================
// Purpose: Sets the keyvalues value
//===================================================================
void keyvalue::SetValue( const char *szKeyName )
{
	if ( !szKeyName )
		return;

	int stringsize = strlen( szKeyName );
	char *ToValue = (char*)malloc(stringsize+1);
	if ( !ToValue )
	{
		assert( !ToValue ); // out of memory.
	}

	// Null out new data.
	memset( ToValue, 0, stringsize + 1 );

	// Set ToName to szKeyName.
	strncpy_s( ToValue, stringsize + 1, szKeyName, stringsize );

	// just in case.
	ToValue[stringsize] = '\0';

	// If we already have a name, free the memory its using.
	if ( value )
		free( value );

	value = NULL;
	value = ToValue;
}

//===================================================================
// Purpose: Gets int value for a key.
//===================================================================
int keyvalue::GetInt( const char *szKeyName, int defaultValue )
{
	if ( !szKeyName )
		return defaultValue;

	for(int i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pKeyValues[i] != NULL )
		{
			if ( _strnicmp( pKeyValues[i]->name, szKeyName, strlen( szKeyName ) ) == 0 )
			{
				//convert to int, return.
				return atoi( pKeyValues[i]->value );
			}
		}
	}

	return defaultValue;
}

//===================================================================
// Purpose: Gets uint64 value for a key.
//===================================================================
long keyvalue::GetLong( const char *szKeyName, long defaultValue )
{
	if ( !szKeyName )
		return defaultValue;

	for(int i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pKeyValues[i] != NULL )
		{
			if ( _strnicmp( pKeyValues[i]->name, szKeyName, strlen( szKeyName ) ) == 0 )
			{
				//convert to long, return.
				return atol( pKeyValues[i]->value );
			}
		}
	}

	return defaultValue;
}

//===================================================================
// Purpose: Gets float value for a key.
//===================================================================
float keyvalue::GetFloat( const char *szKeyName, float defaultValue )
{
	if ( !szKeyName )
		return defaultValue;

	for(int i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pKeyValues[i] != NULL )
		{
			if ( _strnicmp( pKeyValues[i]->name, szKeyName, strlen( szKeyName ) ) == 0 )
			{
				//convert to float, return.
				return (float)atof( pKeyValues[i]->value );
			}
		}
	}

	return defaultValue;
}

//===================================================================
// Purpose: Gets double value for a key.
//===================================================================
double keyvalue::GetDouble( const char *szKeyName, double defaultValue )
{
	if ( !szKeyName )
		return defaultValue;

	for(int i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pKeyValues[i] != NULL )
		{
			if ( _strnicmp( pKeyValues[i]->name, szKeyName, strlen( szKeyName ) ) == 0 )
			{
				//convert to double, return.
				return atof( pKeyValues[i]->value );
			}
		}
	}

	return defaultValue;
}

//===================================================================
// Purpose: Gets boolean value for a key.
//===================================================================
bool keyvalue::GetBool( const char *szKeyName, bool defaultValue )
{
	if ( !szKeyName )
		return defaultValue;

	for(int i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pKeyValues[i] != NULL )
		{
			if ( _strnicmp( pKeyValues[i]->name, szKeyName, strlen( szKeyName ) ) == 0 )
			{
				//determine boolean.
				return atoi( pKeyValues[i]->value )?TRUE:FALSE;
			}
		}
	}

	return defaultValue;
}

//===================================================================
// Purpose: Gets float value for a key.
//===================================================================
const char *keyvalue::GetString( const char *szKeyName, const char *defaultValue )
{
	if ( !szKeyName )
		return defaultValue;

	for(int i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pKeyValues[i] != NULL )
		{
			if ( _strnicmp( pKeyValues[i]->name, szKeyName, strlen( szKeyName ) ) == 0 )
			{
				//return string.
				return pKeyValues[i]->value;
			}
		}
	}

	return defaultValue;
}

//===================================================================
// Purpose: Get wide string value for a key. ( NOTE: Returned wchar is allocated memory, deal with it accordingly. )
//===================================================================
/*const wchar_t *keyvalue::GetWString( const char *szKeyName, const wchar_t *defaultValue )
{
	if ( !szKeyName )
		return defaultValue;

	for(int i = 0; i < MAX_SUB_KEYVALUES; i++ )
	{
		if ( pKeyValues[i] != NULL )
		{
			if ( _strnicmp( pKeyValues[i]->name, szKeyName, strlen( szKeyName ) ) == 0 ) // _strnicmp because of deprecation warning :/
			{
				//convert to wchar_t, return.
				wchar_t *tochar = NULL;
				if ( gsf_ChartoWide( &tochar, pKeyValues[i]->value, strlen(pKeyValues[i]->name) ) )
				{
					return tochar;
				}
				return defaultValue;
			}
		}
	}

	return defaultValue;
}*/