//
//  IExtensions.h
//  Interface for the extensions manager
//
//  Created by Ryan Sheffer on 2013-02-11.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef IEXTENSIONS_H
#define IEXTENSIONS_H

class IExtensions
{
public:
    virtual bool        CreateAllExtensions(void) = 0;
    virtual void        RunExtensions(void) = 0;
    virtual void        DestroyAllExtensions(void) = 0;
    virtual void        SendBuffer(const char *pszSendDest, DataPacking::DataBuffer *pBuffer) = 0;
    virtual DataPacking::DataBuffer *GetSendBuffer(unsigned int index) = 0;
    virtual unsigned int GetNumSendBuffers(void) const = 0;
    virtual void        InvalidateSendBuffers(void) = 0;
};

#endif // IEXTENSIONS_H
