//========= Copyright © 2012-2013, Ryan Sheffers Game Utility Library ==============================//
//
// Purpose: String Helpers
//
//==================================================================================================//

#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

bool IsFilePath(const char *pszFileName);

// Simple little function which modifies the passed in string, removing anything off the end until a forward or back slash
void StripFileName(char *pszFileName);

void StripFileExtension(char *pszFileName);

void StripPathEndSlash(char *pszFileName);

void ReplaceCharacters(char *pszString, char cOriginal, char cReplacement);

const char *NextToken(char *token, const char *str, char sep);

#endif // STRING_HELPERS_H