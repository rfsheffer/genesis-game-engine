//
//  util_stdlib.cpp
//  Utilities Standard C library. Anything we need to declare for platform support goes here.
//  Generally, we will be supporting the standard library that comes with the OS unless
//  we really see a reason (performance reason or other) to redeclare a standard C function
//  here.
//
//  Created by Ryan Sheffer on 14-02-08.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "utilhead.h"
#include "util_stdlib.h"

/**
* Memory Set with debug checking
*/
UTILITIES_FUNCTION
void util_memset(void *dest, int fill, int count)
{
	ASSERTION(count >= 0, "util_memset");
	ASSERT_VALID_WRITE_PTR(dest, count);

	memset(dest,fill,count);
}

/**
* Memory copy with debug checking
*/
UTILITIES_FUNCTION
void util_memcpy(void *dest, const void *src, int count)
{
	ASSERTION(count >= 0, "util_memcpy");
	ASSERT_VALID_READ_PTR(src, count);
	ASSERT_VALID_WRITE_PTR(dest, count);

	memcpy(dest, src, count);
}

/**
* Memory move with debug checking
*/
UTILITIES_FUNCTION
void util_memmove(void *dest, const void *src, int count)
{
	ASSERTION(count >= 0, "util_memmove");
	ASSERT_VALID_READ_PTR(src, count);
	ASSERT_VALID_WRITE_PTR(dest, count);

	memmove(dest, src, count);
}

/**
* Memory compare with debug checking
*/
UTILITIES_FUNCTION
int util_memcmp(const void *m1, const void *m2, int count)
{
	ASSERTION(count >= 0, "util_memcmp");
	ASSERT_VALID_READ_PTR(m1, count);
	ASSERT_VALID_READ_PTR(m2, count);

	return memcmp(m1, m2, count);
}

/**
* strncpy with debug checking and guaranteed NULL termination at maxLen-1
*/
UTILITIES_FUNCTION
void util_strncpy(char *pDest, const char *pSrc, int maxLen)
{
	ASSERTION(maxLen >= 0, "util_strncpy");
	ASSERT_VALID_WRITE_PTR(pDest, maxLen);
	ASSERT_VALID_STRING_PTR(pSrc, maxLen);

	strncpy(pDest, pSrc, maxLen);
	if(maxLen > 0)
	{
		pDest[maxLen-1] = 0;
	}
}

UTILITIES_FUNCTION
int util_stricmp(const char *pStr1, const char *pStr2)
{
    ASSERT_VALID_STRING_PTR(pStr1, 0xFFFFFF);
    ASSERT_VALID_STRING_PTR(pStr2, 0xFFFFFF);

#ifdef _WIN
    return stricmp(pStr1, pStr2);
#elif defined(_MAC) || defined(_LINUX)
    return strcasecmp(pStr1, pStr2);
#endif
}

UTILITIES_FUNCTION
int util_strnicmp(const char *pStr1, const char *pStr2, int maxLen)
{
    ASSERT_VALID_STRING_PTR(pStr1, 0xFFFFFF);
    ASSERT_VALID_STRING_PTR(pStr2, 0xFFFFFF);

#ifdef _WIN
    return strnicmp(pStr1, pStr2, maxLen);
#elif defined(_MAC) || defined(_LINUX)
    return strncasecmp(pStr1, pStr2, maxLen);
#endif
}