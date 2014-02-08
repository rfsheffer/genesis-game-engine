//
//  debug.h
//  Debugging tools
//
//  Created by Ryan Sheffer on 13-01-01.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef DEBUG_H
#define DEBUG_H

#ifdef _WIN
#pragma once
#endif

//------------------------------------------------------------------------------
/**
 * System Calls
 */
#ifdef _WIN
#   ifdef _64BIT
#       define BREAKPOINT __debugbreak()
#       define ABORT exit(1)
#   else
#       define BREAKPOINT do { __asm { int 3 } } while (0)
#       define ABORT      _asm { int 3 }
#   endif
#elif defined(_MAC) || defined(_LINUX)
#   define BREAKPOINT raise(SIGINT)
#   define ABORT       asm("int $3")
#endif

//------------------------------------------------------------------------------
/**
 * Assertions
 */
#ifdef _MAC

// Standard Defined found on the windows API documentation
#define MB_ABORTRETRYIGNORE     0x00000002L

#define IDOK            1
#define IDCANCEL        2
#define IDABORT         3
#define IDRETRY         4
#define IDIGNORE        5
#define IDYES           6
#define IDNO            7
#define IDTRYAGAIN      10
#define IDCONTINUE      11

int MessageBox(void *hWnd, char* lpText, char* lpCaption, unsigned int uType);

#endif

#ifdef _DEBUG

static inline int HandleAsserting(const char *testStr,
                           const char *msgStr,
                           const char *fileStr,
                           int line,
                           int *callFlag, ...)
{
    static char szErrorMessage[1024];
    va_list vl;
    va_start(vl, callFlag);
    vsnprintf(szErrorMessage, 1024, msgStr, vl);
    
    
	// Setup the error message
	static char s_text[2048] = "";
	snprintf(s_text, 2048, "FAILED: %s\nERROR: %s\nFILE '%s', LINE %d\nAbort execution,"
                    " allow assert Retry, or Ignore in the future?",
                    testStr,
                    szErrorMessage,
                    fileStr,
                    line);
    
    static char s_errorHeader[] = "ASSERTION";

	switch(MessageBox(NULL, s_text, s_errorHeader, MB_ABORTRETRYIGNORE))
	{
        case IDIGNORE:      // prevent calling again - turn off flag
            *callFlag=0;    // never call again
            break;
        case IDABORT:       // return flag and break
            return 1;       // abort/break
	}

	return 0;
}

// Windows silently ignores argumentless macros, but GCC needs ## to ignore
// the trailing comma
#if defined(_MAC) || defined(_LINUX)

#define ASSERTION(test, msg, ...) \
{ \
	if(!(test)) \
	{ \
		static int callIt = 1; \
		if(callIt) \
		{ \
			if(HandleAsserting(#test, msg, __FILE__, __LINE__, &callIt, ##__VA_ARGS__)) \
			{ \
				ABORT; \
			} \
		} \
	} \
}

#elif defined(_WIN)

#define ASSERTION(test, msg, ...) \
{ \
	if(!(test)) \
	{ \
		static int callIt = 1; \
		if(callIt) \
		{ \
			if(HandleAsserting(#test, msg, __FILE__, __LINE__, &callIt, __VA_ARGS__)) \
			{ \
				ABORT; \
			} \
		} \
	} \
}

#endif // ASSERTION MACRO

#else

#define ASSERTION(test, msg, ...)

#endif // _DEBUG

//------------------------------------------------------------------------------
/*
 * Cast Debugging
 */
#ifdef _DEBUG
template <typename DEST_TYPE_POINTER, typename SOURCE_TYPE_POINTER>
inline DEST_TYPE_POINTER assert_cast(SOURCE_TYPE_POINTER *pSource)
{
    ASSERTION(static_cast<DEST_TYPE_POINTER>(pSource) ==
              dynamic_cast<DEST_TYPE_POINTER>(pSource),
              "Casting assertion!");
    
    return static_cast<DEST_TYPE_POINTER>(pSource);
}
#else
#define assert_cast static_cast
#endif //_DEBUG

#endif // DEBUG_H