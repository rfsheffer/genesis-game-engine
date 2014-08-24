//
//  string_helpers.h
//  NOTE: These are old depricated functions from old projects. I am trying
//        to decide if they are worth keeping for something. Please don't use
//        them.
//
//  Created by Ryan Sheffer on 2012-11-18.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

#ifdef _WIN
#pragma once
#endif

namespace Utility
{
    bool IsFilePath(const char *pszFileName);
    
    // Simple little function which modifies the passed in string, removing anything off the end until a forward or back slash
    void StripFileName(char *pszFileName);
    
    void StripFileExtension(char *pszFileName);
    
    void StripPathEndSlash(char *pszFileName);
    
    void ReplaceCharacters(char *pszString, char cOriginal, char cReplacement);
    
    const char *NextToken(char *token, const char *str, char sep);
}
#endif // STRING_HELPERS_H