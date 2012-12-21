//========= Copyright © 2012-2013, Ryan Sheffers Game Utility Library ==============================//
//
// Purpose: A class used for parsing and changing folder paths
//
//==================================================================================================//

#ifndef UTIL_FILE_PATH_H
#define UTIL_FILE_PATH_H

#include "util_string.h"

class CUtlFilePath : public CUtlString
{
public:

	CUtlFilePath(const char *pszInputStr);
	CUtlFilePath(size_t numChars);
	CUtlFilePath() : CUtlString()
	{
		m_uiPathDepth = 0;
	}

	// File Extension
	bool			HasFileExtension(void) const;
	void			StripFileExtension(void);
	const char		*GetFileExtension(void) const;

	// File Name
	bool			HasFileName(void) const {return m_bHasFileName;}
	void			AppendFileName(const char *szFileName);
	void			StripFileName(void);
	const char		*GetFileName(void) const;

	// Adding to path
	void			PushFolder(const char *szFolderName);
	void			PopFolder(void);

	// The depth of the path, where the root folder is 0
	size_t			PathDepth(void) const {return m_uiPathDepth;}

	// Slightly slower functions for getting elements from a path string
	void			GetFileExtension(char *pDest, size_t destlen) const;
	void			GetFileName(char *pDest, size_t destlen, bool extension = true) const;

	// Functions which are considered more expensive because they create a CUtlString
	// to copy the needed characters then return another copy
	//CUtlString		GetFileExtension(void) const;
	//CUtlString		GetFileName(bool extension = true) const;

private:

	void			SetupPath(void);

	size_t			m_uiPathDepth;

	bool			m_bHasFileName;
	bool			m_bHasFileExtension;
};


#endif // UTIL_FILE_PATH_H