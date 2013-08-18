//
//  util_keyvalues.h
//  A keyvalues (KV) file parser and creator.
//
//  Created by Ryan Sheffer on 2013-04-21.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef UTIL_KEY_VALUES_H
#define UTIL_KEY_VALUES_H

#include "util_variant.h"

namespace Utility
{
    /**
     * Keyvalues File Parser, Creator
     */
    class Keyvalues
    {
    public:
        
        /** Sets some defaults */
        Keyvalues();
        
        /** Primary destruction */
        ~Keyvalues();
        
        bool        PopulateWithFile(FileHandle pFile, const char *pszRootName);
        bool        PopulateWithBuffer(const char *pszBuffer, size_t buffSize, const char *pszRootName);
        bool        PopulateFile(FileHandle pFile);
        
        /** Returns true if this key is a branch containing children */
        inline bool HasChildren(void) const { return m_uiNumChildren != 0; }
        
        /** The max size of a keyvalue string */
        static const unsigned int   MAX_KEYVALUE_STRING_SIZE = 64;
        
        /** Gets the name of the key */
        inline const char *GetName(void) const { return m_szName; }
        
        /** Gets the variant assigned to the key */
        inline const Variant<MAX_KEYVALUE_STRING_SIZE>
                            &GetVariant(void) const { return m_value; }
        
        /** Gets the first child of this branch */
        inline const Keyvalues *GetFirstChild(void) const { return m_ppChildren[0]; }
        
        /** Gets the next keyvalue after this one, the next in a line of children */
        inline const Keyvalues *GetNextChild(void) const { return m_pRightBrother; }
        
        Keyvalues       *GetKey(const char *pszKeyName) const;
        inline int      GetInt(const char *pszKeyName = NULL, int defaultValue = 0) const;
        inline float    GetFloat(const char *pszKeyName = NULL, float defaultValue = 0.0f) const;
        inline bool		GetBool(const char *pszKeyName = NULL, bool defaultValue = 0) const;
        inline const char  *GetString(const char *pszKeyName = NULL, const char *defaultValue = "") const;
        
        Keyvalues       *CreateKey(const char *pszKeyName);
        
        bool            WriteBranch(FileHandle pFile, unsigned int level);
        
    protected:
        
        bool        SkipCommentLines(const char **pszBuffer, size_t &buffSize);
        
    private:
        
        void        AddChild(Keyvalues *pKeyvalue);
        
        void        SetName(const char *pszName, size_t nameLength);
        void        SetValue(const char *pszValue, size_t valLength);
        
        bool        ParseKey(const char **pszBuffer, size_t &buffSize);
        
        /** A linked list of child keyvalues */
        Keyvalues                   **m_ppChildren;
        
        /** For quick iteration, we are keeping pointers to brother keys */
        Keyvalues                   *m_pRightBrother;
        
        /** Number of children assigned to this key */
        unsigned int                m_uiNumChildren;
        
        /** The name of this key */
        char                        m_szName[MAX_KEYVALUE_STRING_SIZE];
        
        /** The value contained in this keyvalue */
        Variant<MAX_KEYVALUE_STRING_SIZE>  m_value;
        
        /** Types of characters we run into while parsing a KV script */
        enum KVCharType
        {
            KVCTYPE_WHITESPACE,
            KVCTYPE_LEFT_BRACKET,
            KVCTYPE_RIGHT_BRACKET,
            KVCTYPE_DOUBLE_QUOTE,
            KVCTYPE_FSLASH,
            KVCTYPE_TEXT_CHAR,
            KVCTYPE_IGNORE
        };
        
        /** The number of ASCII characters we bother checking */
        static const unsigned int   NUM_USED_ASCII_CHARS = 256;
        
        /**
         This will return a type which can be passed to a switch.
         No need for a function with an ifelse tree.
         */
        static KVCharType           s_charTranslator[NUM_USED_ASCII_CHARS];
        
        /** True when the translation array as been initialized */
        static bool                 s_bTranslatorInit;
    };
    
    //--------------------------------------------------------------------------
    /**
     * Gets the integer from the variant stored in this key.
     * @param pszKeyName The key to search for. Setting this parameter to NULL
     *                   will return the variant of this key.
     * @param defaultValue The default value to return if no key could be found.
     */
    inline int Keyvalues::GetInt(const char *pszKeyName, int defaultValue) const
    {
        if(pszKeyName != NULL)
        {
            const Keyvalues *pKey = GetKey(pszKeyName);
            return (pKey != NULL)?pKey->GetVariant().GetInt():defaultValue;
        }
        
        return m_value.GetInt();
    }
    
    //--------------------------------------------------------------------------
    /**
     * Gets the float from the variant stored in this key.
     * @param pszKeyName The key to search for. Setting this parameter to NULL
     *                   will return the variant of this key.
     * @param defaultValue The default value to return if no key could be found.
     */
    inline float Keyvalues::GetFloat(const char *pszKeyName, float defaultValue) const
    {
        if(pszKeyName != NULL)
        {
            const Keyvalues *pKey = GetKey(pszKeyName);
            return (pKey != NULL)?pKey->GetVariant().GetFloat():defaultValue;
        }
        
        return m_value.GetFloat();
    }
    
    //--------------------------------------------------------------------------
    /**
     * Gets the float from the variant stored in this key.
     * @param pszKeyName The key to search for. Setting this parameter to NULL
     *                   will return the variant of this key.
     * @param defaultValue The default value to return if no key could be found.
     */
    inline bool Keyvalues::GetBool(const char *pszKeyName, bool defaultValue) const
    {
        if(pszKeyName != NULL)
        {
            const Keyvalues *pKey = GetKey(pszKeyName);
            return (pKey != NULL)?pKey->GetVariant().GetBool():defaultValue;
        }
        
        return m_value.GetBool();
    }
    
    //--------------------------------------------------------------------------
    /**
     * Gets the float from the variant stored in this key.
     * @param pszKeyName The key to search for. Setting this parameter to NULL
     *                   will return the variant of this key.
     * @param defaultValue The default value to return if no key could be found.
     */
    inline const char *Keyvalues::GetString(const char *pszKeyName, const char *defaultValue) const
    {
        if(pszKeyName != NULL)
        {
            const Keyvalues *pKey = GetKey(pszKeyName);
            return (pKey != NULL)?pKey->GetVariant().GetString():defaultValue;
        }
        
        return m_value.GetString();
    }
}

#endif // UTIL_KEY_VALUES_H
