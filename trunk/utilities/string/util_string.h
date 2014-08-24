//
//  util_string.h
//  A string helper class.
//
//  Created by Ryan Sheffer on 2013-04-21.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#ifdef _WIN
#pragma once
#endif

// Memory for the string is allocated in steps of MEM_ALLOC_STRIDE bytes
#define MEM_ALLOC_STRIDE		4

namespace Utility
{
//-----------------------------------------------------------------------------
// String container class
//-----------------------------------------------------------------------------
class CUtlString
{
public:
	// construct
	CUtlString(const char *pszInputStr);
	CUtlString(size_t numChars);
	CUtlString()
	{
		m_pszStr = NULL;
		m_uiNumCharacters = 0;
		m_uiNumAllocBytes = 0;
	}

	// destruct
	~CUtlString()
	{
		if(m_pszStr)
			free(m_pszStr);
	}

	// copy
	CUtlString(CUtlString &inString);

	inline const char *GetStr(void) const {return m_pszStr;}
	inline void Clear(void)
	{
		if(m_pszStr)
		{
			// Can't see why I should waste time doing this...
			/*for(size_t i = 0; i < m_uiNumCharacters; ++i)
			{
				m_pszStr[i] = '\0';
			}*/

			m_pszStr[0] = '\0';
			m_uiNumCharacters = 0;
		}
	}

	// I thought about this function, and it seems pointless to me. I am leaving it out for now.
	//inline bool EnsureSize(size_t numChars){return SetupMem(numChars + 1);}

	inline bool IsEmpty(void) const {return m_uiNumCharacters == 0;}

	inline size_t GetNumCharacters(void) const { return m_uiNumCharacters; }
	inline size_t GetNumAllocated(void) const { return m_uiNumAllocBytes; }

	// Character Replacement
	//void ReplaceCharacters(char cReplacement, size_t numElems, ...);
	void ReplaceCharacters(char cOriginal, char cReplacement);

	// String Comparison
	int CompareStringsCaseSensitive(const CUtlString &otherStr) const;
	int CompareStringsCaseInsensitive(const CUtlString &otherStr) const;

	inline bool operator==(const CUtlString &otherStr) const;
	inline bool operator!=(const CUtlString &otherStr) const;

	// Sting Concat
	void ConcatString(const CUtlString &otherStr);
	void ConcatString(const char *pszOther);

	inline CUtlString&	operator+=(const CUtlString &otherStr);
	inline CUtlString&	operator+=(const char *pszOther);

	void PushCharacter(char cAppChar);

	// General Utility
	void ToLowerCase(void);
	void ToUpperCase(void);

	// Character Removal
	void RemoveCharacters(size_t startChar = 0, size_t numChars = -1);
	void PopCharacters(size_t numChars = 1);

	size_t CountCharacters(char cCharacter) const;

	void VarArgs(char *format, ...);

	const char *NextToken(char *token, const char *str, char sep);

	// Element access
	char operator[](size_t i) const
	{
		ASSERTION(i < m_uiNumCharacters, "CUtlString: Element out of range!");
		return m_pszStr[i];
	}

	const char &Element(size_t i) const
	{
		ASSERTION(i < m_uiNumCharacters, "CUtlString: Element out of range!");
		return m_pszStr[i];
	}

private:
	 
	bool SetupMem(size_t numChars);

	// Expensive
	CUtlString	operator+(const CUtlString& otherStr) const;

	// Not Allowed
	char& operator[](size_t i);
	CUtlString	operator=(const CUtlString& otherStr) const;

	// The actual character string
	char				*m_pszStr;

	// Sizes
	size_t		m_uiNumCharacters;
	size_t		m_uiNumAllocBytes;
};

inline bool CUtlString::operator==(const CUtlString &otherStr) const
{
	return CompareStringsCaseSensitive(otherStr) == 0;
}

inline bool CUtlString::operator!=(const CUtlString &otherStr) const
{
	return CompareStringsCaseSensitive(otherStr) != 0;
}

inline CUtlString&	CUtlString::operator+=(const CUtlString &otherStr)
{
	ConcatString(otherStr);
	return *this;
}

inline CUtlString& CUtlString::operator+=(const char *pszOther)
{
	ConcatString(pszOther);
	return *this;
}
    
} // namespace Utility

#endif // UTIL_STRING_H