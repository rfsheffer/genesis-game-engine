//========= Copyright © 2012-2013, Ryan Sheffers Game Utility Library ==============================//
//
// Purpose: Parses scripts with keyvalue based syntax.
//
//==================================================================================================//

#ifndef UTIL_KEYVALUES_H
#define UTIL_KEYVALUES_H


#define MAX_SUB_KEYVALUES	1024		// This is per keyvalue subset.

// Keyvalues class.
class keyvalue
{
public:

	keyvalue()
	{
		node = false;
		name = NULL;
		value = NULL;
		pKVParent = NULL;
		bracket_open = false;

		for( int i = 0; i < MAX_SUB_KEYVALUES; i++ )
			pKeyValues[i] = NULL;
	}
	~keyvalue()
	{
		if ( name )
			free( name );
		if ( value )
			free( value );

		for ( int i = 0; i < MAX_SUB_KEYVALUES; i++ )
		{
			if ( pKeyValues[i] != NULL )
			{
				delete pKeyValues[i];
				pKeyValues[i] = NULL;
			}
		}
		pKVParent = NULL;
	}

	bool node;								// Node?

	// TODO: Allow this to be a dictionary or a vector depending on maybe a template?
	keyvalue *pKeyValues[MAX_SUB_KEYVALUES];	// Child objects.

	char *name;								// Raw data.
	char *value;							// Raw data. (Note: Nodes do not have values.)

	keyvalue *pKVParent;					// Parent keyvalue.
	bool bracket_open;						// During parse, this tells whether this keyvalue has its bracket open to accept new child keyvalues.


	// Keyvalue Functions

	// Find a keyValue.
	// Set bCreate to true to create the key if it doesn't already exist (which ensures a valid pointer will be returned)
	keyvalue	*FindKey( const char *szKeyName, bool bCreate = false );

	// Gets the next keyvalue in line on the level pCurrentKey is on.
	keyvalue	*GetNextKey( keyvalue *pCurrentKey );
	// Gets the next keyvalue in line on the level pCurrentKey is on, by pCurrentKey name.
	// ryan: Re-write this function, its pretty lame.
	//keyvalue	*GetNextKeyByName( keyvalue *pCurrentKey );

	void	SetName( const char *szKeyName );
	void	SetValue( const char *szKeyName );

	// Getting Data
	int			GetInt( const char *szKeyName = NULL, int defaultValue = 0 );
	long		GetLong( const char *szKeyName = NULL, long defaultValue = 0 );
	float		GetFloat( const char *szKeyName = NULL, float defaultValue = 0.0f );
	double		GetDouble( const char *szKeyName = NULL, double defaultValue = 0.0 );
	bool		GetBool( const char *szKeyName = NULL, bool defaultValue = 0 );
	const		char *GetString( const char *szKeyName = NULL, const char *defaultValue = "" );

	unsigned int	GetNumKeys(void)
	{
		unsigned int i = 0;
		for(i = 0; i < MAX_SUB_KEYVALUES; ++i)
			if(pKeyValues[i] == NULL)
				break;

		return i;
	}

	// Disabled for this app.
	//const		wchar_t *GetWString( const char *szKeyName = NULL, const wchar_t *defaultValue = L"" );
};

// Global Keyvalue Functions.
bool ParseKVScript( const char *szScriptName, int stringsize, keyvalue **pReturnKV, bool isfile );
bool CreateKVScript( char *szScriptName, keyvalue *pWriteKV );
keyvalue *CreateNewKVBlock( char *szScriptName );
keyvalue *CreateNewKVNode( char *szNodeName, keyvalue *pParent );
bool CreateNewKVValue( const char *szName, const char *szValue, keyvalue *pNode );

#endif // UTIL_KEYVALUES_H