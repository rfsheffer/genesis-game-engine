//
//  util_string.cpp
//  A string helper class.
//
//  Created by Ryan Sheffer on 2013-04-21.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "allhead.h"
#include "util_string.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CUtlString::CUtlString(const char *pszInputStr)
{
	m_uiNumAllocBytes = 0;

	if(pszInputStr)
	{
		m_uiNumCharacters = strlen(pszInputStr);
		if(!SetupMem(m_uiNumCharacters + 1))
		{
			m_uiNumCharacters = 0;
		}
		else
		{
			for(size_t i = 0; i < m_uiNumCharacters; ++i)
			{
				m_pszStr[i] = pszInputStr[i];
			}
			m_pszStr[m_uiNumCharacters] = '\0';
		}
	}
}

CUtlString::CUtlString(size_t numChars)
{
	m_uiNumAllocBytes = 0;

	if(SetupMem(numChars + 1))
	{
		m_uiNumCharacters = numChars;
	}
	else
	{
		m_uiNumCharacters = 0;
	}
}

//-----------------------------------------------------------------------------
// Copy Constructor
//-----------------------------------------------------------------------------
CUtlString::CUtlString(CUtlString &inString)
{
	if(inString.GetNumCharacters())
	{
		m_uiNumCharacters = inString.GetNumCharacters();
		if(!SetupMem(m_uiNumCharacters + 1))
		{
			m_uiNumCharacters = 0;
		}
		else
		{
			for(size_t i = 0; i < m_uiNumCharacters; ++i)
			{
				m_pszStr[i] = inString.Element(i);
			}
			m_pszStr[m_uiNumCharacters] = '\0';
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: Sets up the memory for this string based on the number of string characters
//-----------------------------------------------------------------------------
bool CUtlString::SetupMem(size_t numChars)
{
	if(numChars != 0)
	{
		if(m_uiNumAllocBytes == 0)
		{
			// Align to our memory alloc stride
			m_uiNumAllocBytes = (size_t)ceil((float)numChars / MEM_ALLOC_STRIDE) * MEM_ALLOC_STRIDE;
			m_pszStr = (char*)malloc(m_uiNumAllocBytes);
		}
		else if(numChars > m_uiNumAllocBytes)
		{
			// We need to increase the size of this string
			m_uiNumAllocBytes = (size_t)ceil((float)numChars / MEM_ALLOC_STRIDE) * MEM_ALLOC_STRIDE;
			m_pszStr = (char*)realloc(m_pszStr, m_uiNumAllocBytes);
		}

		ASSERTION(m_pszStr, "CUtlString: Out of Memory?");
	}

	return (m_pszStr != NULL);
}

//-----------------------------------------------------------------------------
// Purpose: Replaces a variable number of characters with a single character
//-----------------------------------------------------------------------------
/*
void CUtlString::ReplaceCharacters(char cReplacement, size_t numElems, ...)
{
	va_list ap;
	size_t i = 0, j = 0;

	if(m_uiNumCharacters == 0)
		return;

	for(i = 0; i < m_uiNumCharacters; ++i)
	{
		va_start(ap, numElems);
		for(j = 0; j < numElems; ++j)
		{
			char c = va_arg(ap, char);
			if(m_pszStr[i] == c)
			{
				m_pszStr[i] = cReplacement;
				break;
			}
		}
		va_end(ap);
	}
}
 */

//-----------------------------------------------------------------------------
// Purpose: Replaces a specific character in a string with another character
//-----------------------------------------------------------------------------
void CUtlString::ReplaceCharacters(char cOriginal, char cReplacement)
{
	if(m_uiNumCharacters == 0)
		return;

	for(size_t i = 0; i < m_uiNumCharacters; ++i)
	{
		if(m_pszStr[i] == cOriginal)
		{
			m_pszStr[i] = cReplacement;
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: String Comparison Case Sensitive
//-----------------------------------------------------------------------------
int CUtlString::CompareStringsCaseSensitive(const CUtlString &otherStr) const
{
	if(m_uiNumCharacters > otherStr.GetNumCharacters())
		return 1;
	if(m_uiNumCharacters < otherStr.GetNumCharacters())
		return -1;

	size_t i = 0;
	while(i < m_uiNumCharacters)
	{
		if(m_pszStr[i] > otherStr[i])
			return 1;
		else if(m_pszStr[i] < otherStr[i])
			return -1;
		++i;
	}

	return 0;
}

//-----------------------------------------------------------------------------
// Purpose: String Comparison Case Insensitive
//-----------------------------------------------------------------------------
int CUtlString::CompareStringsCaseInsensitive(const CUtlString &otherStr) const
{
	if(m_uiNumCharacters > otherStr.GetNumCharacters())
		return 1;
	if(m_uiNumCharacters < otherStr.GetNumCharacters())
		return -1;

	size_t i = 0;
	while(i < m_uiNumCharacters)
	{
		if(toupper(m_pszStr[i]) > toupper(otherStr[i]))
			return 1;
		else if(toupper(m_pszStr[i]) < toupper(otherStr[i]))
			return -1;
		++i;
	}

	return 0;
}

//-----------------------------------------------------------------------------
// Purpose: Concatenate string on the end of this string
//-----------------------------------------------------------------------------
void CUtlString::ConcatString(const CUtlString &otherStr)
{
	if(otherStr.IsEmpty())
		return;

	// Check if this string needs to be resized to fit the concatenation
	if(SetupMem(m_uiNumCharacters + otherStr.GetNumCharacters() + 1))
	{
		for(size_t i = 0; i < otherStr.GetNumCharacters(); ++i)
		{
			m_pszStr[m_uiNumCharacters + i] = otherStr[i];
		}

		m_uiNumCharacters = m_uiNumCharacters + otherStr.GetNumCharacters();
		m_pszStr[m_uiNumCharacters] = '\0';
	}
}

//-----------------------------------------------------------------------------
// Purpose: Concatenate character string on the end of this string
//-----------------------------------------------------------------------------
void CUtlString::ConcatString(const char *pszOther)
{
	if(!pszOther)
		return;

	size_t otherStrLen = strlen(pszOther);
	if(otherStrLen == 0)
		return;

	// Check if this string needs to be resized to fit the concatenation
	if(SetupMem(m_uiNumCharacters + otherStrLen + 1))
	{
		for(size_t i = 0; i < otherStrLen; ++i)
		{
			m_pszStr[m_uiNumCharacters + i] = pszOther[i];
		}

		m_uiNumCharacters = m_uiNumCharacters + otherStrLen;
		m_pszStr[m_uiNumCharacters] = '\0';
	}
}

//-----------------------------------------------------------------------------
// Purpose: Appends a single character on the end of this string
//-----------------------------------------------------------------------------
void CUtlString::PushCharacter(char cAppChar)
{
	// Make sure we have enough alloc memory
	if(SetupMem(m_uiNumCharacters + 2))
	{
		// Add the new character to the end
		m_pszStr[m_uiNumCharacters] = cAppChar;

		// Increase the num chars count and add the null terminator
		m_uiNumCharacters = m_uiNumCharacters + 1;
		m_pszStr[m_uiNumCharacters] = '\0';
	}
}

//-----------------------------------------------------------------------------
// Purpose: Converts the string to lower case
//-----------------------------------------------------------------------------
void CUtlString::ToLowerCase(void)
{
	for(size_t i = 0; i < m_uiNumCharacters; ++i)
	{
		m_pszStr[i] = tolower(m_pszStr[i]);
	}
}

//-----------------------------------------------------------------------------
// Purpose: Converts the string to upper case
//-----------------------------------------------------------------------------
void CUtlString::ToUpperCase(void)
{
	for(size_t i = 0; i < m_uiNumCharacters; ++i)
	{
		m_pszStr[i] = toupper(m_pszStr[i]);
	}
}

//-----------------------------------------------------------------------------
// Purpose: Removes a number of characters from the string starting at startChar and removing until numChars or NULL terminator
//-----------------------------------------------------------------------------
void CUtlString::RemoveCharacters(size_t startChar, size_t numChars)
{
	if(startChar >= m_uiNumCharacters)
	{
		ASSERTION(false, "CUtlString: startChar in RemoveCharacters is out of range!");
		return;
	}

	// Clearing the whole thing?
	if(startChar == 0 && numChars == size_t(-1))
	{
		Clear();
		return;
	}

	// Gotta make sure we don't wrap around
	if(numChars == size_t(-1))
	{
		numChars = m_uiNumCharacters;
	}

	while(startChar < m_uiNumCharacters)
	{
		// Check if we have gone off the end, and if so just NULL out
		if((startChar + numChars) >= m_uiNumCharacters)
		{
			m_pszStr[startChar] = '\0';
			m_uiNumCharacters = startChar;
			break;
		}
		else
		{
			// Copy the chars back to the position we are stripping out from the end of the strip
			m_pszStr[startChar] = m_pszStr[startChar + numChars];
		}

		// Just break when we see the NULL terminator
		if(m_pszStr[startChar] == '\0')
		{
			m_uiNumCharacters = startChar;
			break;
		}

		++startChar;
	}
}

//-----------------------------------------------------------------------------
// Purpose: Removes a variable number of characters from the end of the string
//-----------------------------------------------------------------------------
void CUtlString::PopCharacters(size_t numChars)
{
	if(m_uiNumCharacters == 0)
		return;

	for(int i = int(m_uiNumCharacters - 1); (i >= 0) && (numChars > 0); --i, --numChars)
	{
		m_pszStr[i] = '\0';
		--m_uiNumCharacters;
	}
}

//-----------------------------------------------------------------------------
// Purpose: returns the number of characters which match the input character
//-----------------------------------------------------------------------------
size_t CUtlString::CountCharacters(char cCharacter) const
{
	size_t count = 0;
	for(size_t i = 0; i < m_uiNumCharacters; ++i)
	{
		if(m_pszStr[i] == cCharacter)
			++count;
	}

	return count;
}

//-----------------------------------------------------------------------------
// Purpose: Returns the next token in a string
//-----------------------------------------------------------------------------
const char *CUtlString::NextToken(char *token, const char *str, char sep)
{
	// Check the end of the string vs the input string
	if(str == &m_pszStr[m_uiNumCharacters])
	{
		return NULL;
	}

	// If the input string is NULL, start it off with this string
	if((str == NULL) || (*str == '\0'))
	{
		str = m_pszStr;
	}

#ifdef _DEBUG
	// Checking if str isn't even in range of this string
	ASSERTION((str >= m_pszStr) && (str <= &m_pszStr[m_uiNumCharacters]), "Passed in string to NextToken is out of range of this strings memory!");
#endif

	// Copy everything up to the first separator into the return buffer.
	// Do not include separators in the return buffer.
	while((*str != sep) && (*str != '\0'))
	{
		*token++ = *str++;
	}
	*token = '\0';

	// Advance the pointer unless we hit the end of the input string.
	if(*str == '\0')
	{
		return str;
	}

	return ++str;
}

//-----------------------------------------------------------------------------
// Purpose: Replaces the contents of this string with a string containing variable arguments
// Input  : *format - The format to add to the string
//			... - The arguments to replace the symbols in format with
//-----------------------------------------------------------------------------
void CUtlString::VarArgs(char *format, ...)
{
	va_list			argptr;
	static char		str[1024];

	va_start(argptr, format);
	vsnprintf(str, sizeof(str), format, argptr);
	va_end(argptr);

	m_uiNumCharacters = strlen(str);

	if(SetupMem(m_uiNumCharacters + 1))
	{
		strncpy(m_pszStr, str, m_uiNumCharacters);
	}
}