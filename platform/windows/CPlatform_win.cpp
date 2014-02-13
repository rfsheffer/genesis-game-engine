//
//  CPlatform.cpp
//  Extension for platform control on the MAC.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "allhead.h"
#include "CPlatform.h"

//------------------------------------------------------------------------------
/**
 * Initialization of the platform. This will happen after the extension
 * manager has been created.
 */
void CPlatform::Initialize(void)
{
    
}

//------------------------------------------------------------------------------
/**
 * Called usually at the end of program execution.
 */
void CPlatform::Shutdown(void)
{
    
}

//extern hWindow GetActiveWindow(void);

#define ACTIVE_WINDOW_ASSERT(str)  ASSERTION(GetActiveWindow(), "Active window is invalid in " str)

//------------------------------------------------------------------------------
/**
 * Gets the state ( true[on] or false[off] of a keyboard key.
 * @param character The key to check.
 */
bool CPlatform::GetKeyState(char character) const
{
    ACTIVE_WINDOW_ASSERT("GetKeyState");
    
    return false;
}

//------------------------------------------------------------------------------
/**
 * Gets the state ( true[on] or false[off] of a mouse button.
 * @param left If true, returns the state of the left mouse button.
 */
bool CPlatform::GetMouseState(bool left) const
{
    ACTIVE_WINDOW_ASSERT("GetMouseState");
    
    return false;
}

//------------------------------------------------------------------------------
/**
 * Gets a window handle by name
 * @param pszWindowName The name of the window
 * @return The window handle
 */
hWindow CPlatform::GetWindowHandle(const char *pszWindowName) const
{
    return GetActiveWindow();
}

//------------------------------------------------------------------------------
/**
 * Sets the active window to update
 * @param index The index of the active window.
 */
void CPlatform::SetActiveWindow(hWindow index) const
{

}

//------------------------------------------------------------------------------
/**
 * Gets the size of the active window in pixels
 * @param width Width will be put in this reference variable
 * @param height Height will be put in this reference variable
 */
void CPlatform::GetWindowSizePixels(unsigned int &width, unsigned int &height) const
{
    
}

//------------------------------------------------------------------------------
/**
 * Gets the size of the active windows graphics area
 * @param width Width will be put in this reference variable
 * @param height Height will be put in this reference variable
 */
void CPlatform::GetWindowSize(unsigned int &width, unsigned int &height) const
{
    
}

//------------------------------------------------------------------------------
/**
 * Activates the graphics context for the current active window.
 */
void CPlatform::ActivateGraphicsContext(void) const
{
    
}

//------------------------------------------------------------------------------
/**
 * Presents the fullscreen color buffer to the screen.
 */
void CPlatform::SwapGraphicsContextBuffers(void) const
{
    
}

//------------------------------------------------------------------------------
/**
 * Gets the absolute path to the application executable.
 */
const char *CPlatform::GetAbsoluteApplicationPath(void) const
{
    static char szFileLine[MAX_PATH]; szFileLine[0] = '\0';
    //static const char *appdir = " ";
    //strncat(szFileLine, appdir, MAX_PATH);
    
    // Take off the file name
    for(int i = MAX_PATH - 1; i >= 0; --i)
    {
        if(szFileLine[i] == '/')
        {
            break;
        }

        szFileLine[i] = '\0';
    }
    
    return szFileLine;
}

//------------------------------------------------------------------------------
/**
 * Opens a file and returns a handle to that file.
 * Note that the handle will need to be released manually.
 * @param pszFileName The name of the file to open.
 * @param pszOptions The options string.
 * @see platform_constants.h for a list of file IO options.
 */
FileHandle CPlatform::FileOpen(const char *pszFileName, const char *pszOptions) const
{
    return fopen(pszFileName, pszOptions);
}

//------------------------------------------------------------------------------
/**
 * Reads from a file to a buffer at ptr. Note that this will fail if the file isn't writeable.
 * @param ptr A pointer to the buffer to read to.
 * @param chunkSize The chunk size in bytes to read in at a time.
 * @param chunkCount The number of chunks to read in.
 * @param pFile The file handle to read from.
 * @return The number of bytes read.
 */
size_t CPlatform::FileRead(void *ptr, size_t chunkSize, size_t chunkCount, FileHandle pFile) const
{
    return fread(ptr, chunkSize, chunkCount, pFile);
}

//------------------------------------------------------------------------------
/**
 * Writes the buffer at ptr to pFile. Note that this will fail if the file isn't writeable.
 * @param ptr A pointer to the buffer to write to pFile.
 * @param chunkSize The chunk size in bytes to write out at a time.
 * @param chunkCount The number of chunks to write out.
 * @param pFile The file handle to write to.
 * @return The number of bytes written.
 */
size_t CPlatform::FileWrite(const void *ptr, size_t chunkSize, size_t chunkCount, FileHandle pFile) const
{
    return fwrite(ptr, chunkSize, chunkCount, pFile);
}

//------------------------------------------------------------------------------
/**
 * Gets the size of the file in bytes.
 * @param pFile The file to get the size of.
 * @return The size of the file.
 */
size_t CPlatform::GetFileSize(FileHandle pFile) const
{
    fpos_t pos;
    int err = fgetpos(pFile, &pos);
    ASSERTION(err == 0, "GetFileSize: fgetpos has failed!");
    
    fseek(pFile, 0, SEEK_END);   // non-portable
    size_t size = ftell(pFile);
    
    err = fsetpos(pFile, &pos);
    ASSERTION(err == 0, "GetFileSize: fsetpos has failed!");
    
    return size;
}