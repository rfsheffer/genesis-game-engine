//
//  util_keyvalues.cpp
//  A keyvalues (KV) file parser and creator.
//
//  Created by Ryan Sheffer on 2013-04-21.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

/*------------------------------------------------------------------------------
 
 KEYVALUES FILE ( KV )
 A keyvalues file is a plain text document containing a simple tree like structure.
 The structure consists of branches which contain other branches or key/valve pairs.
 
 A simple keyvalue script might look like this:
 
 "hello_keyvalues"
 {
    "key"       "value"
 
    "branch"
    {
        "key"       "value"
    }
 }
 
 Note: Both single line and multi-line C style comments are acceptable in a KV file.
 Note: To enforce the rule that whitespace is ignored, all keys and values must be
        contained within double quotes.
 Note: Using double quotes within a key or value will result in a syntax error.
 
 -----------------------------------------------------------------------------*/

#include "allhead.h"
#include "keyvalues.h"
#include "ascii_table.h"

namespace Utility
{
    // Declaring all the statics
    const unsigned int Keyvalues::MAX_KEYVALUE_STRING_SIZE;
    const unsigned int Keyvalues::NUM_USED_ASCII_CHARS;
    Keyvalues::KVCharType Keyvalues::s_charTranslator[Keyvalues::NUM_USED_ASCII_CHARS];
    bool Keyvalues::s_bTranslatorInit;
    
    //--------------------------------------------------------------------------
    /**
     * Constructor
     */
    Keyvalues::Keyvalues()
    {
        m_ppChildren = NULL;
        m_uiNumChildren = 0;
        m_szName[0] = '\0';
        m_value.SetInt(0);
        m_pRightBrother = NULL;
        
        // Build the quick translation lookup table. This only happens
        // the first time keyvalues are used.
        if(s_bTranslatorInit == false)
        {
            for(char c = 0; c < NUM_USED_ASCII_CHARS; ++c)
            {
                if(c == ASCII_LEFT_BRACKET)
                {
                    s_charTranslator[c] = KVCTYPE_LEFT_BRACKET;
                }
                else if(c == ASCII_RIGHT_BRACKET)
                {
                    s_charTranslator[c] = KVCTYPE_RIGHT_BRACKET;
                }
                else if(c == ASCII_DOUBLE_QUOTE)
                {
                    s_charTranslator[c] = KVCTYPE_DOUBLE_QUOTE;
                }
                else if(c == ASCII_SPACE)
                {
                    s_charTranslator[c] = KVCTYPE_WHITESPACE;
                }
                else if(c == ASCII_FSLASH)
                {
                    s_charTranslator[c] = KVCTYPE_FSLASH;
                }
                else if(c < ASCII_SPACE)
                {
                    // Anything below the space character is useless whitespace
                    // and will be ignored.
                    s_charTranslator[c] = KVCTYPE_IGNORE;
                }
                else
                {
                    s_charTranslator[c] = KVCTYPE_TEXT_CHAR;
                }
            }
            
            s_bTranslatorInit = true;
        }
    }
    
    //--------------------------------------------------------------------------
    /**
     * Destructor
     */
    Keyvalues::~Keyvalues()
    {
        for(size_t i = 0; i < m_uiNumChildren; ++i)
        {
            delete m_ppChildren[i];
            m_ppChildren[i] = NULL;
        }
        
        if(m_ppChildren)
        {
            delete m_ppChildren;
            m_ppChildren = NULL;
        }
    }
    
    //--------------------------------------------------------------------------
    /**
     * Populates the keyvalues structure with the unparsed character string
     * structure contained in a KV file.
     * @param pFile The file to parse.
     * @return True on success
     */
    bool Keyvalues::PopulateWithFile(FileHandle pFile, const char *pszRootName)
    {
        ASSERTION(pFile != NULL, "Keyvalues::PopulateWithFile, Invalid file pointer!");
        
        size_t fileLen = GetPlatform()->GetFileSize(pFile);
        
        char *pFileBuffer = new char[fileLen];
        
        GetPlatform()->FileRead(pFileBuffer, 1, fileLen, pFile);
        
        bool ret = PopulateWithBuffer(pFileBuffer, fileLen, pszRootName);
        
        delete [] pFileBuffer;
        
        // TODO: We need a way of reporting this error in release builds as well.
#ifdef _DEBUG
        static char strErr[256];
        if(ret == false)
        {
            strErr[0] = '\0';
            strncat(strErr, "Could not load keyvalues for ", 256);
            strncat(strErr, pszRootName, 256);
            ASSERTION(ret != false, strErr);
        }
#endif

        return ret;
    }
    
    //--------------------------------------------------------------------------
    /**
     * Populates the keyvalues structure with the unparsed structure from a
     * character buffer.
     * @param pszBuffer The buffer to parse.
     * @param buffSize The size of the buffer.
     * @return True on success
     */
    bool Keyvalues::PopulateWithBuffer(const char *pszBuffer, size_t buffSize, const char *pszRootName)
    {
        // First key is always the root.
        strncpy(m_szName, pszRootName, MAX_KEYVALUE_STRING_SIZE);
        m_szName[MAX_KEYVALUE_STRING_SIZE - 1] = '\0'; // Just in case...
        
        // Parse the first key. Normally, it will be a branch. If it is a
        // keyvalue, then the creator is doing something odd, but it isn't
        // going to hurt anything... It's just odd.
        if(ParseKey(&pszBuffer, buffSize) == false)
        {
            ASSERTION(false, "Could not load keyvalues from buffer");
            return false;
        }
        
        return true;
    }
    
    //--------------------------------------------------------------------------
    /**
     * Parses from a buffer, a keyvalue pair or branch
     * @param pszBuffer The buffer
     * @param buffSize The size of the buffer
     * @return True on success
     */
    bool Keyvalues::ParseKey(const char **ppszBuffer, size_t &buffSize)
    {
        // This is so we can setup a linked list for fast iteration of keys
        // @see m_pRightBrother
        Keyvalues       *pevKey = NULL;
        
        // Create a child key early
        Keyvalues       *key = new Keyvalues;
        
        bool            ignoreWhites = true;
        char            keyName[MAX_KEYVALUE_STRING_SIZE];
        unsigned int    keyname_pos = 0;
        
        bool            bFinished = false;
        bool            bRet = true;
        
        while(bFinished == false && buffSize != 0)
        {            
            switch(s_charTranslator[**ppszBuffer])
            {
                case KVCTYPE_IGNORE:
                {
                    // Shift the buffer forward
                    ++(*ppszBuffer);
                    --buffSize;
                    break;
                }
                case KVCTYPE_LEFT_BRACKET:
                {
                    if(*key->GetName() == '\0')
                    {
                        ASSERTION(*key->GetName() != '\0', "Keyvalues syntax error: Name not set before left bracket!");
                        bFinished = true;
                        bRet = false;
                        break;
                    }
                    
                    // We need to shift the buffer forward here instead before
                    // starting a new ParseKey function call so that { won't
                    // be evaluated again.
                    ++(*ppszBuffer);
                    --buffSize;
                    
                    bRet = key->ParseKey(ppszBuffer, buffSize);
                    if(bRet == false)
                    {
                        bFinished = true;
                        break;
                    }
                    
                    // Add the branch to us as a child
                    AddChild(key);
                    
                    // Setup iteration helper
                    if(pevKey != NULL)
                    {
                        pevKey->m_pRightBrother = key;
                    }
                    pevKey = key;
                    
                    // Create new key for further parsing
                    key = new Keyvalues;
                    
                    break;
                }
                case KVCTYPE_RIGHT_BRACKET:
                {                    
                    bFinished = true;
                    
                    // Shift the buffer forward
                    ++(*ppszBuffer);
                    --buffSize;
                    break;
                }
                case KVCTYPE_DOUBLE_QUOTE:
                {
                    // Sections in quotes allow us to have spaces and such in names.
                    ignoreWhites = !ignoreWhites;
                    
                    // If ignore whites was turned back on, we know a string has
                    // ended. Set either the key name or the value.
                    if(ignoreWhites == true)
                    {
                        keyName[keyname_pos] = '\0';
                        
                        if(*key->GetName() == '\0')
                        {
                            key->SetName(keyName, keyname_pos + 1);
                        }
                        else
                        {
                            key->SetValue(keyName, keyname_pos);
                            
                            // This is a value, add the key
                            AddChild(key);
                            
                            // Setup iteration helper
                            if(pevKey != NULL)
                            {
                                pevKey->m_pRightBrother = key;
                            }
                            pevKey = key;
                            
                            // Start a new one
                            key = new Keyvalues;
                        }
                        
                        keyname_pos = 0;
                    }
                    
                    // Shift the buffer forward
                    ++(*ppszBuffer);
                    --buffSize;
                    break;
                }
                case KVCTYPE_FSLASH:
                {
                    // Could be a comment, run a check. If not, fall through.
                    if(ignoreWhites == true && SkipCommentLines(ppszBuffer, buffSize))
                    {
                        // We don't shift the buffer forward here because
                        // it was already done in SkipCommentLines.
                        break;
                    }
                    
                    keyName[keyname_pos++] = **ppszBuffer;
                    
                    // Shift the buffer forward
                    ++(*ppszBuffer);
                    --buffSize;
                    break;
                }
                case KVCTYPE_WHITESPACE:
                {
                    if(ignoreWhites == true)
                    {
                        // Shift the buffer forward
                        ++(*ppszBuffer);
                        --buffSize;
                        break;
                    }
                    
                    keyName[keyname_pos++] = **ppszBuffer;
                    
                    // Shift the buffer forward
                    ++(*ppszBuffer);
                    --buffSize;
                    break;
                }
                case KVCTYPE_TEXT_CHAR:
                {                    
                    keyName[keyname_pos++] = **ppszBuffer;
                    
                    if(ignoreWhites != false)
                    {
                        ASSERTION(ignoreWhites == false, "Keyvalues syntax error: Writting characters outside of double quotes.");
                        bFinished = true;
                        bRet = false;
                    }
                    
                    // Shift the buffer forward
                    ++(*ppszBuffer);
                    --buffSize;
                    break;
                }
                    
                default:
                {
                    ASSERTION(false, "ParseKey: Unknown key type in array?");
                    bFinished = true;
                    bRet = false;
                }
            }
            
            if((keyname_pos + 1) >= MAX_KEYVALUE_STRING_SIZE)
            {
                bFinished = true;
                ASSERTION((keyname_pos + 1) < MAX_KEYVALUE_STRING_SIZE,
                          "Keyvalues syntax error: Maxiumum key string size exceeded!");
                bRet = false;
            }
        }
        
        // Key created? We aren't using it so delete it.
        if(key)
        {
            delete key;
            key = NULL;
        }
        
        return bRet;
    }
    
    //--------------------------------------------------------------------------
    void AddIndentation(FileHandle pFile, unsigned int level)
    {
        while(level != 0)
        {
            GetPlatform()->FileWrite("\t", 1, 1, pFile);
            --level;
        }
    }
    
    //--------------------------------------------------------------------------
    /**
     * Writes a name with double quotes around it to the file.
     * @note It is important that pszName is no longer than MAX_KEYVALUE_STRING_SIZE - 1
     */
    void WriteName(FileHandle pFile, const char *pszName)
    {
        static char szNameBuff[Keyvalues::MAX_KEYVALUE_STRING_SIZE + 2];
        size_t nameLen = strlen(pszName);
        
        szNameBuff[0] = '\"';
        strcpy(&szNameBuff[1], pszName);
        szNameBuff[nameLen + 1] = '\"';
        
        GetPlatform()->FileWrite(szNameBuff, 1, nameLen + 2, pFile);
    }
    
    //--------------------------------------------------------------------------
    /**
     * Writes a name with double quotes around it to the file.
     * @note It is important that pszName is no longer than MAX_KEYVALUE_STRING_SIZE - 1
     */
    void WriteVariant(FileHandle pFile,
                      const char *pszName,
                      const Variant *pVar)
    {        
        WriteName(pFile, pszName);
        GetPlatform()->FileWrite(" ", 1, 1, pFile);
        WriteName(pFile, pVar->ToString());
    }
    
    //--------------------------------------------------------------------------
    /**
     * Populates a file with a text representation of this key structure
     * @param pFile The file to populate
     * @param level The indentation level
     */
    bool Keyvalues::WriteBranch(FileHandle pFile, unsigned int level)
    {
        if(level == 0)
        {
            const char *pszFileHeader = "// Auto-Generated Keyvalue Script\n\n";
            GetPlatform()->FileWrite(pszFileHeader, 1, sizeof(pszFileHeader), pFile);
        }
        
        AddIndentation(pFile, level);
        WriteName(pFile, GetName());
        GetPlatform()->FileWrite("\n", 1, 1, pFile);
        AddIndentation(pFile, level);
        GetPlatform()->FileWrite("{\n", 1, 1, pFile);
        
        for(unsigned int i = 0; i < m_uiNumChildren; ++i)
        {
            Keyvalues *pKey = m_ppChildren[i];
            if(pKey->HasChildren())
            {
                if(pKey->WriteBranch(pFile, level + 1) == false)
                {
                    return false;
                }
            }
            else
            {
                AddIndentation(pFile, level + 1);
                WriteVariant(pFile, pKey->GetName(), &pKey->GetVariant());
                GetPlatform()->FileWrite("\n", 1, 1, pFile);
            }
        }
        
        AddIndentation(pFile, level);
        GetPlatform()->FileWrite("}\n", 1, 1, pFile);
        return true;
    }
    
    //--------------------------------------------------------------------------
    /**
     * Populates a file with a text representation of this key structure
     * @param pFile The file to populate
     * @param level The indentation level
     */
    bool Keyvalues::PopulateFile(FileHandle pFile)
    {
        const char *pszFileHeader = "// Auto-Generated Keyvalue Script\n\n";
        GetPlatform()->FileWrite(pszFileHeader, 1, sizeof(pszFileHeader), pFile);
        
        for(unsigned int i = 0; i < m_uiNumChildren; ++i)
        {
            if(m_ppChildren[i]->WriteBranch(pFile, 0) == false)
            {
                return false;
            }
        }
        
        return true;
    }
    
    //--------------------------------------------------------------------------
    /**
     * Adds a new child to this keyvalue. This in turn, makes this a branch key
     * @param pKeyvalue The keyvalue to add
     */
    void Keyvalues::AddChild(Keyvalues *pKeyvalue)
    {
        if(m_uiNumChildren == 0)
        {
            m_ppChildren = (Keyvalues **)malloc(sizeof(Keyvalues **));
            ASSERTION(m_ppChildren, "Keyvalues::AddChild failed to allocate memory");
        }
        else
        {
            Keyvalues **temp =
            (Keyvalues **)realloc(m_ppChildren,
                                  sizeof(Keyvalues **) * (m_uiNumChildren + 1));
            
            ASSERTION(temp != NULL, "Keyvalues::AddChild failed to allocate memory");
            
            m_ppChildren = temp;
        }
        
        m_ppChildren[m_uiNumChildren] = pKeyvalue;
        ++m_uiNumChildren;
    }
    
    //--------------------------------------------------------------------------
    /**
     * Sets the name of this key.
     * @param pszName The value to determine.
     * @param nameLength The size of the input buffer.
     */
    void Keyvalues::SetName(const char *pszName, size_t nameLength)
    {
        strncpy(m_szName, pszName, nameLength);
    }
    
    //--------------------------------------------------------------------------
    /**
     * Determines the type of element in pszValue, and sets the correct value.
     * @param pszValue The value to determine.
     * @param valLength The size of the input buffer.
     * @note This is a real simple checking function and you could trick it with
     * a value like "56fg.345f" which would evalute it as a float, however, all
     * that will be stored will be 56. I don't think this really matters, it's
     * still safe. ~RFS
     */
    void Keyvalues::SetValue(const char *pszValue, size_t valLength)
    {
        bool isFloating = false;
        
        if((*pszValue >= ASCII_ZERO && *pszValue <= ASCII_NINE) || *pszValue == '-')
        {
            for(size_t i = 0; i < valLength; ++i)
            {
                if(pszValue[i] == ASCII_PERIOD)
                {
                    isFloating = true;
                    break;
                }
            }
            
            if(isFloating)
            {
                m_value.SetFloat(atof(pszValue));
            }
            else
            {
                m_value.SetInt(atoi(pszValue));
            }
        }
        else
        {
            ASSERTION(false, "Strings unsupported at the moment for keyvalues.");
            //m_value.SetString(pszValue);
        }
    }
    
    //--------------------------------------------------------------------------
    /**
     * Takes in a buffer, skips any comment lines, and returns the next
     * uncommented line.
     * @param pszBuffer Buffer to check.
     */
    bool Keyvalues::SkipCommentLines(const char **ppszBuffer, size_t &buffSize)
    {
        if(buffSize < 2)
        {
            // There couldn't possibly be a comment here
            return false;
        }
        
        enum comment_type
        {
            COMMENT_LINE,
            COMMENT_SECTION
        };
        
        comment_type type = COMMENT_LINE;
        
        if((*ppszBuffer)[0] == '/')
        {
            if((*ppszBuffer)[1] == '/')
            {
                type = COMMENT_LINE;
            }
            else if((*ppszBuffer)[1] == '*')
            {
                type = COMMENT_SECTION;
            }
            else
            {
                // There is no comment
                return false;
            }
        }
        
        buffSize -= 2;
        (*ppszBuffer) += 2;
        
        if(type == COMMENT_LINE)
        {
            // We go forward till a newline
            while(buffSize > 0)
            {
                // Comment removal is interesting because it is the only time
                // where white space is even considered in C like languages.
                if(*(*ppszBuffer) == ASCII_LF) // Carriage return
                {
                    break;
                }
                
                ++(*ppszBuffer);
                --buffSize;
            }
        }
        else
        {
            // Go till a "*/"
            while(buffSize > 0)
            {
                if(*(*ppszBuffer) == '*')
                {
                    if(*((*ppszBuffer) + 1) == '/')
                    {
                        buffSize -= 2;
                        (*ppszBuffer) += 2;
                        break;
                    }
                }
                
                ++(*ppszBuffer);
                --buffSize;
            }
        }
        
        return true;
    }
    
    //--------------------------------------------------------------------------
    /**
     * Gets a child key by name.
     * @param pszKeyName The name of the key to get.
     */
    Keyvalues *Keyvalues::GetKey(const char *pszKeyName) const
    {
        for(unsigned int i = 0; i < m_uiNumChildren; ++i)
        {
            if(strncasecmp(m_ppChildren[i]->GetName(),
                           pszKeyName,
                           MAX_KEYVALUE_STRING_SIZE) == 0)
            {
                return m_ppChildren[i];
            }
        }
        
        return NULL;
    }
    
    //--------------------------------------------------------------------------
    /**
     * Creates a new key and adds it to the children of this branch.
     * @param pszKeyName The name of the key to create.
     */
    Keyvalues *Keyvalues::CreateKey(const char *pszKeyName)
    {
        ASSERTION(pszKeyName != NULL && pszKeyName[0] != '\0',
                  "Keyvalues::CreateKey: Trying to create nameless key!");
        
        Keyvalues *key = new Keyvalues;
        AddChild(key);
        
        key->SetName(pszKeyName, strlen(pszKeyName));
        
        return key;
    }
}