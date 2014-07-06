//
//  util_filepath.cpp
//  A class used for parsing and changing folder paths
//
//  Created by Ryan Sheffer on 2013-04-21.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "utilhead.h"
#include "util_filepath.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CUtlFilePath::CUtlFilePath(const char *pszInputStr) : CUtlString(pszInputStr)
{
	m_uiPathDepth = 0;
	m_bHasFileName = false;

	// Determine the depth of the possible path
	SetupPath();
}

CUtlFilePath::CUtlFilePath(size_t numChars) : CUtlString(numChars)
{
	m_uiPathDepth = 0;
	m_bHasFileName = false;
}

//-----------------------------------------------------------------------------
// Purpose: Sets up a path string
//-----------------------------------------------------------------------------
void CUtlFilePath::SetupPath(void)
{
	if(GetNumCharacters() == 0)
	{
		m_uiPathDepth = 0;
		m_bHasFileName = false;
		return;
	}

	// Fixup the path to conform to forward slash
	ReplaceCharacters('\\', '/');

	// Determine if there is a file name on the end
	for(int i = (int)GetNumCharacters() - 1; i >= 0; --i)
	{
		// break if there is a slash
		if(Element(i) == '/')
			break;

		// the first sighting of a '.' means this path has an extension
		if(Element(i) == '.')
		{
			m_bHasFileName = true;
			break;
		}
	}

	// Append an ending slash if needed
	if(!m_bHasFileName && Element(GetNumCharacters() - 1) != '/')
	{
		PushCharacter('/');
	}

	int pathdepth = (int)CountCharacters('/') - 1;

	if(pathdepth < 0)
    {
        m_uiPathDepth = 0;
    }
    else
    {
        m_uiPathDepth = pathdepth;
    }
}

//-----------------------------------------------------------------------------
// Purpose: Returns a pointer to the extension part of the string
//-----------------------------------------------------------------------------
const char *CUtlFilePath::GetFileExtension(void) const
{
	if(!m_bHasFileName || GetNumCharacters() == 0)
    {
		return NULL;
    }

    int numCharacters = (int)GetNumCharacters();
	for(int i = (numCharacters - 1); i >= 0; --i)
	{
		// Look for the '.' of the extension
		if(Element(i) == '.')
		{
			return &Element(i + 1);
		}
	}

	ASSERTION_ALWAYS("CUtlFilePath: Found no extension even though this is a file path!");
	return NULL;
}

//-----------------------------------------------------------------------------
// Purpose: Appends a file name to this path
//-----------------------------------------------------------------------------
void CUtlFilePath::AppendFileName(const char *szFileName)
{
	if(!szFileName)
		return;

	// Sanity check the new string coming in.
	// It cannot contain a path or be missing an extension
	bool hasExtension = false;
	for(size_t i = 0; i < strlen(szFileName); ++i)
	{
		if(szFileName[i] == '.')
		{
			hasExtension = true;
		}

		if(szFileName[i] == '/' || szFileName[i] == '\\')
			return;
	}

	// If there is already a file name, strip it and replace with the new one
	if(hasExtension)
	{
		StripFileName();
	}
	else
		return;

	ConcatString(szFileName);
	m_bHasFileName = true;
}

//-----------------------------------------------------------------------------
// Purpose: Returns the file name including the extension
//-----------------------------------------------------------------------------
void CUtlFilePath::StripFileName(void)
{
	if(!m_bHasFileName)
		return;

	int i;
	for(i = (int)GetNumCharacters() - 1; i >= 0; --i)
	{
		if(Element(i) == '/')
			break;
	}

	PopCharacters(GetNumCharacters() - i);

	m_bHasFileName = false;
}

//-----------------------------------------------------------------------------
// Purpose: Returns a pointer to the filename part of the string, which will also include the extension if there is one
//-----------------------------------------------------------------------------
const char *CUtlFilePath::GetFileName(void) const
{
	if(!m_bHasFileName)
		return NULL;

	for(int i = (int)GetNumCharacters() - 1; i >= 0; --i)
	{
		if(Element(i) == '/')
			return &Element(i + 1);
	}

	ASSERTION_ALWAYS("CUtlFilePath: Found no file name even though this is a file path!");
	return NULL;
}

//-----------------------------------------------------------------------------
// Purpose: Adds a folder or multiple folders to the end of this folder list
//-----------------------------------------------------------------------------
void CUtlFilePath::PushFolder(const char *szFolderName)
{
	if(!szFolderName)
		return;

	// If the structure being passed in has a / or \\ at the start, it is considered incorrect.
	// Might change this to fix the string being passed in, but an assertion would still be thrown as a performance warning.
	if(szFolderName[0] == '\\' || szFolderName[0] == '/')
	{
		ASSERTION(!(szFolderName[0] == '\\' || szFolderName[0] == '/'), "CUtlFilePath: Pushing folders with a starting slash is not allowed!");
		return;
	}

	// Strip off the file name if there is one
	StripFileName();

	ConcatString(szFolderName);
	SetupPath();
}

//-----------------------------------------------------------------------------
// Purpose: Pops off the folder on the end of this folder list.
// Note: If there is a file name on the end it will also be dropped.
//-----------------------------------------------------------------------------
void CUtlFilePath::PopFolder(void)
{
	if(GetNumCharacters() == 0 || m_uiPathDepth == 0)
		return;

	int numToKeep = (int)GetNumCharacters() - 1;
	if(Element(numToKeep) == '/')
	{
		// If there is a slash on the end, jump it
		--numToKeep;
	}

	while(numToKeep >= 0)
	{
		if(Element(numToKeep) == '/')
		{
			// Include the filename if there is one in the pop
			if(m_bHasFileName)
			{
				m_bHasFileName = false;
			}
			else
			{
				break;
			}
		}

		--numToKeep;
	}

	// We need to get this out of zero based so we add 1 back
	++numToKeep;

	PopCharacters(GetNumCharacters() - numToKeep);

	--m_uiPathDepth;

	m_bHasFileName = m_bHasFileExtension = false;
}

//-----------------------------------------------------------------------------
// Purpose: returns the file extension for this path
//-----------------------------------------------------------------------------
void CUtlFilePath::GetFileExtension(char *pDest, size_t destlen) const
{
    UNREFERENCED_PARAMETER(pDest);
    UNREFERENCED_PARAMETER(destlen);
}

//-----------------------------------------------------------------------------
// Purpose: returns the file name for this path
//-----------------------------------------------------------------------------
void CUtlFilePath::GetFileName(char *pDest, size_t destlen, bool extension) const
{
    UNREFERENCED_PARAMETER(pDest);
    UNREFERENCED_PARAMETER(destlen);
    UNREFERENCED_PARAMETER(extension);
}