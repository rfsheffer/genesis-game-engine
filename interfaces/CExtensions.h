//
//  CExtensions.h
//  genesis
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef CEXTENSIONS_H
#define CEXTENSIONS_H

#include "IServer.h"
#include "IClient.h"
#include "IPlatform.h"
#include "iExtension.h"

#define MAX_BASE_EXTENSIONS         5

class CExtensions
{
public:
    CExtensions() : m_uiNumExtensions(0) {}
    
    DECLARE_IMPORT_EXTENSION(Server);
    DECLARE_IMPORT_EXTENSION(Client);
    
    bool        CreateAllExtensions(void);
    
    void        RunExtensions(void);
    
    void        DestroyAllExtensions(void);
    
    inline IPlatform   *GetPlatform(){ return pPlatform; }
    
private:
    
    unsigned int    m_uiNumExtensions;
    iExtension      *pExtensions[MAX_BASE_EXTENSIONS];
    
    IPlatform       *pPlatform;
};


#endif // CEXTENSIONS_H
