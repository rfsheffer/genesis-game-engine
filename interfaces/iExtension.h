//
//  iExtension.h
//  Base Extension
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef IEXTENSION_H
#define IEXTENSION_H

class iExtension
{
public:
    virtual void Run(void) = 0;
};

#define DECLARE_IMPORT_EXTENSION(name) \
public: \
    inline I##name     *Get##name() { return p##name##Extension; } \
private: \
    void        *p##name##Handle; \
    I##name     *p##name##Extension; \
public:

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

#define CLOSE_IMPORT_EXTENSION(name) \
dlclose(p##name##Handle);

#define START_EXTENSION_INTERFACE(name) \
class CExtensions; \
\
class I##name : public iExtension \
{ \
public: \
    virtual void            Initialize(CExtensions *pExtensions) = 0; \
    virtual void            Shutdown() = 0;

#define END_EXTENSION_INTERFACE() };

#define SETUP_EXTENSION_LINK(name) \
DLL_EXPORT \
I##name *__Create##name(void) \
{ \
    return new C##name(); \
}

#endif // IEXTENSION_H