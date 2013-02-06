//
//  iExtension.h
//  Base Extension
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef IEXTENSION_H
#define IEXTENSION_H

/*! \file iExtension.h
 \brief Extension Interface Macros and Interface class.
 
 Details.
 */

namespace DataPacking
{
    class DataBuffer;
}

/*! Extension Interface */
class iExtension
{
public:
    virtual void Run(void) = 0;
};

/*! \def DECLARE_IMPORT_EXTENSION(name)
 \brief A macro for declaring a dynamically imported extension.
 
 Details.
 */
#define DECLARE_IMPORT_EXTENSION(name) \
public: \
    inline I##name     *Get##name() { return p##name##Extension; } \
private: \
    void        *p##name##Handle; \
    I##name     *p##name##Extension; \
public:

/*! \def DEFINE_IMPORT_EXTENSION(libname, name)
 \brief A macro for defining a dynamically imported extension.
 
 Details.
 */
#define DEFINE_IMPORT_EXTENSION(libname, name) \
    p##name##Handle = dlopen(libname, RTLD_NOW); \
    if(p##name##Handle == NULL) \
    { \
        ASSERTION(p##name##Handle, "Unable to connect to " #name " extension!"); \
        return false; \
    } \
\
    I##name     *(*__##name)(void); \
    *(void **)(&__##name) = dlsym(p##name##Handle, "__Create"#name); \
\
    if(__##name) \
    { \
        p##name##Extension = (*__##name)(); \
    }

/*! \def CLOSE_IMPORT_EXTENSION(name)
 \brief A macro for closing a dynamically imported extension. Used at shutdown.
 
 Details.
 */
#define CLOSE_IMPORT_EXTENSION(name) \
dlclose(p##name##Handle);

/*! \def START_EXTENSION_INTERFACE(name)
 \brief A macro for starting a new interface. Declare any variables or functions
 after this macro is placed.
 
 Details.
 */
#define START_EXTENSION_INTERFACE(name) \
class CExtensions; \
\
class I##name : public iExtension \
{ \
public: \
    virtual void            Initialize(CExtensions *pExtensions) = 0; \
    virtual void            Shutdown() = 0; \
    virtual void            RecvDataBuffer(DataPacking::DataBuffer *pBuffer) = 0;

/*! \def END_EXTENSION_INTERFACE()
 \brief A macro for ending a new extension.
 
 Details.
 */
#define END_EXTENSION_INTERFACE() };

/*! \def SETUP_EXTENSION_LINK()
 \brief A macro for setting up a link for a dynamic extension to be loaded.
 
 Details.
 */
#define SETUP_EXTENSION_LINK(name) \
DLL_EXPORT \
I##name *__Create##name(void) \
{ \
    return new C##name(); \
}

#endif // IEXTENSION_H