//
//  IPlatform.h
//  Extension for accessing platform information.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef IPLATFORM_H
#define IPLATFORM_H

#define PLATFORM_INTERFACE_NAME     "platform"
#define PLATFORM_INTERFACE_VERSION  1

/**
 * Interface for the Platform Extension
 */
class IPlatform
{
public:
    
    //--------------------------------------------------------------------------
    // INITIALIZATION
    //--------------------------------------------------------------------------
    /**
     * Platform initialization.
     */
    virtual void    Initialize(void) = 0;
    
    /**
     * Platform shutdown.
     */
    virtual void    Shutdown(void) = 0;
    
    //--------------------------------------------------------------------------
    // INPUT
    //--------------------------------------------------------------------------
    /**
     * Gets the state ( true[on] or false[off] of a keyboard key.
     * @param character The key to check.
     */
    virtual bool    GetKeyState(char character) const = 0;
    
    /**
     * Gets the state ( true[on] or false[off] of a mouse button.
     * @param left If true, returns the state of the left mouse button.
     */
    virtual bool    GetMouseState(bool left) const = 0;
    
    //--------------------------------------------------------------------------
    // WINDOW
    //--------------------------------------------------------------------------
    
    /**
     * Gets a window handle by name.
     * @param pszWindowName The name of the window
     * @return The handle to the window.
     */
    virtual hWindow     GetWindowHandle(const char *pszWindowName) const = 0;
    
    /**
     * Sets the active window to update
     * @param index The index of the active window. 
     */
    virtual void    SetActiveWindow(hWindow index) const = 0;
    
    /**
     * Gets the size of the active window in pixels
     * @param width Width will be put in this reference variable
     * @param height Height will be put in this reference variable
     */
    virtual void    GetWindowSizePixels(unsigned int &width, unsigned int &height) const = 0;
    
    /**
     * Gets the size of the active windows graphics area
     * @param width Width will be put in this reference variable
     * @param height Height will be put in this reference variable
     */
    virtual void    GetWindowSize(unsigned int &width, unsigned int &height) const = 0;
    
    //--------------------------------------------------------------------------
    // GRAPHICS CONTEXT
    //--------------------------------------------------------------------------
    /**
     * Activates the graphics context for the currently active window.
     */
    virtual void    ActivateGraphicsContext(void) const = 0;
    
    /**
     * Presents the fullscreen color buffer to the screen.
     */
    virtual void    SwapGraphicsContextBuffers(void) const = 0;
    
    //--------------------------------------------------------------------------
    // FILE SYSTEM
    //--------------------------------------------------------------------------
    /**
     * Gets the absolute path to the application directory.
     */
    virtual const char *GetAbsoluteApplicationPath(void) const = 0;
    
    /**
     * Opens a file and returns a handle to that file.
     * Note that the handle will need to be released manually.
     * @param pszFileName The name of the file to open.
     * @param pszOptions The options string.
     * @see platform_constants.h for a list of file IO options.
     */
    virtual FileHandle FileOpen(const char *pszFileName, const char *pszOptions) const = 0;
    
    /**
     * Reads from a file to a buffer at ptr. Note that this will fail if the file isn't writeable.
     * @param ptr A pointer to the buffer to read to.
     * @param chunkSize The chunk size in bytes to read in at a time.
     * @param chunkCount The number of chunks to read in.
     * @param pFile The file handle to read from.
     * @return The number of bytes read.
     */
    virtual size_t FileRead(void *ptr, size_t chunkSize, size_t chunkCount, FileHandle pFile) const = 0;
    
    /**
     * Writes the buffer at ptr to pFile. Note that this will fail if the file isn't writeable.
     * @param ptr A pointer to the buffer to write to pFile.
     * @param chunkSize The chunk size in bytes to write out at a time.
     * @param chunkCount The number of chunks to write out.
     * @param pFile The file handle to write to.
     * @return The number of bytes written.
     */
    virtual size_t FileWrite(const void *ptr, size_t chunkSize, size_t chunkCount, FileHandle pFile) const = 0;
    
    /**
     * Gets the size of the file in bytes.
     * @param pFile The file to get the size of.
     * @return The size of the file.
     */
    virtual size_t GetFileSize(FileHandle pFile) const = 0;
};

//------------------------------------------------------------------------------
/**
 * A helper to get the platform pointer.
 * @note The platform pointer should always be valid in any case. This function
 *       should be defined and the pointer should return where you created the
 *       platform element.
 */
IPlatform *GetPlatform(void);


#endif // IPLATFORM_H
