//========= Copyright � 2012-2013, Ryan Sheffers Game Utility Library ==============================//
//
// Purpose: String helper functions
//
//==================================================================================================//

#include "allhead.h"

bool IsFilePath(const char *pszFileName)
{
	int strlength = strlen(pszFileName);
	if(strlength == 0)
		return false;

	bool foundExtension = false;

	--strlength;
	while(strlength >= 0)
	{
		if(pszFileName[strlength] == '\\' || pszFileName[strlength] == '/')
			return foundExtension;

		if(pszFileName[strlength] == '.')
			foundExtension = true;

		--strlength;
	}

	return false;
}

// Simple little function which modifies the passed in string, removing anything off the end until a forward or back slash
void StripFileName(char *pszFileName)
{
	if(!pszFileName)
		return;

	if(!IsFilePath(pszFileName))
		return;

	int strlength = strlen(pszFileName);
	if(strlength == 0)
		return;

	--strlength;
	while(strlength >= 0)
	{
		if(pszFileName[strlength] == '\\' || pszFileName[strlength] == '/')
		{
			pszFileName[strlength] = '\0';
			break;
		}

		pszFileName[strlength] = '\0';
		--strlength;
	}
}

void StripFileExtension(char *pszFileName)
{
	if(!pszFileName)
		return;

	int strlength = strlen(pszFileName);
	if(strlength == 0)
		return;

	--strlength;
	while(strlength >= 0)
	{
		if(pszFileName[strlength] == '.')
		{
			pszFileName[strlength] = '\0';
			break;
		}

		--strlength;
	}
}

void StripPathEndSlash(char *pszFileName)
{
	if(!pszFileName)
		return;

	int strlength = strlen(pszFileName) - 1;
	if(strlength <= 0)
		return;

	if(pszFileName[strlength] == '\\' || pszFileName[strlength] == '/')
	{
		pszFileName[strlength] = '\0';
	}
}

void ReplaceCharacters(char *pszString, char cOriginal, char cReplacement)
{
	if(!pszString)
		return;

	size_t strLength = strlen(pszString);
	for(unsigned int i = 0; i < strLength; ++i)
	{
		if(pszString[i] == cOriginal)
		{
			pszString[i] = cReplacement;
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: Slightly modified strtok. Does not modify the input string. Does
//			not skip over more than one separator at a time. This allows parsing
//			strings where tokens between separators may or may not be present:
//
//			Door01,,,0 would be parsed as "Door01"  ""  ""  "0"
//			Door01,Open,,0 would be parsed as "Door01"  "Open"  ""  "0"
//
// Input  : token - Returns with a token, or zero length if the token was missing.
//			str - String to parse.
//			sep - Character to use as separator. UNDONE: allow multiple separator chars
// Output : Returns a pointer to the next token to be parsed.
//-----------------------------------------------------------------------------
const char *NextToken(char *token, const char *str, char sep)
{
	if ((str == NULL) || (*str == '\0'))
	{
		*token = '\0';
		return(NULL);
	}

	//
	// Copy everything up to the first separator into the return buffer.
	// Do not include separators in the return buffer.
	//
	while ((*str != sep) && (*str != '\0'))
	{
		*token++ = *str++;
	}
	*token = '\0';

	//
	// Advance the pointer unless we hit the end of the input string.
	//
	if (*str == '\0')
	{
		return(str);
	}

	return(++str);
}