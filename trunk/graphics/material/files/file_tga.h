//
//  file_tga.h
//  Used for loading a TGA file
//
//  Created by Ryan Sheffer on 2012-10-31.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef FILE_TGA_H
#define FILE_TGA_H

#ifdef _WIN32
#pragma once
#endif

namespace FileTypes
{
    
#define TGA_FILE_NONE       0
#define TGA_FILE_RGB        0x00000001
#define TGA_FILE_RGBA       0x00000002
    
    // The headers to a TGA file
    /*struct TGATypeHeader
    {
        byte Header[12];
    };
    
    struct TGAHeader
    {
        byte		header[6];			// First 6 Useful Bytes From The Header
        UINT32		bytesPerPixel;		// Holds Number Of Bytes Per Pixel Used In The TGA File
        UINT32		imageSize;			// Used To Store The Image Size When Setting Aside Ram
        UINT32		temp;				// Temporary Variable
        UINT32		type;
        UINT32		Height;				// Height of Image
        UINT32		Width;				// Width ofImage
        UINT32		Bpp;				// Bits Per Pixel
    };*/

    // Top of the File Header
    struct TGAHeader
    {
        byte  idlength;
        byte  colourmaptype;
        byte  imageType;
    };
    
    // Color map information, for pallets
    struct TGAColorMapSpec
    {
        short   colorMapFirstEntry;
        short   colorMapLength;
        byte    colorMapEntrySize;
    } __attribute__ ((__packed__));
    
    // Image dimensions
    struct TGAImageSpec
    {
        short xorigin;
        short yorigin;
        short imageWidth;
        short imageHeight;
        byte pixelDepth;
        byte imageDesc;
    };
    
    // TGA loader class
    class CTGAFile
    {
    public:
        
        CTGAFile()
        {
            // Initialize values on creation
            //m_szMaterialName[0] = '\0';
            //m_pData = NULL;
            //m_iBPP = 0;
            //m_iWidth = 0;
            //m_iHeight = 0;
        }
        
        // Loads a TGA file, checks if it's uncompressed or compressed.
        bool LoadTGA(const char *pszfilename);

    private:
        
        // Load an Uncompressed file
        //bool LoadUncompressedTGA(const char *pszfilename, FILE *fTGA);
        
        // Load a Compressed file
        //bool LoadCompressedTGA(const char *pszfilename, FILE *fTGA);
        
        // Name of the texture
        //char	m_szMaterialName[MAX_TEX_NAME_LEN];
        
        // Image Data (Up To 32 Bits)
        //byte        *m_pData;
        
        // Image Color Depth In Bits Per Pixel
        //unsigned int m_iBPP;
        
        // Image Width
        //unsigned int m_iWidth;
        
        // Image Height
        //unsigned int m_iHeight;
        
        // Image Type (GL_RGB, GL_RGBA)
        //int         m_ITypeFlags;
    };
    
}

#endif // FILE_TGA_H






