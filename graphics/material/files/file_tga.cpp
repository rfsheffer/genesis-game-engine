//
//  file_tga.cpp
//  Used for loading a TGA file
//
//  Created by Ryan Sheffer on 2012-10-31.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "file_tga.h"

namespace FileTypes
{
    // Simple comparison arrays
    //static byte s_bUTGACompare[12] = {0,0,2, 0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
    //static byte s_bCTGACompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};	// Compressed TGA Header
     
     
    bool CTGAFile::LoadTGA(const char *pszfilename)
    {
        if(!pszfilename)
            return false;
        
        FILE *pTGAFIle = fopen(pszfilename, "rb");
        if(!pTGAFIle)
            return false;
        
#ifdef _DEBUG
        ASSERTION(sizeof(TGAHeader) == 3, "Incorrect TGA Header Size!");
        ASSERTION(sizeof(TGAColorMapSpec) == 5, "Incorrect TGA color spec Size!");
        ASSERTION(sizeof(TGAImageSpec) == 10, "Incorrect TGA image spec Size!");
#endif
        
        
        TGAHeader header;
        fread(&header, sizeof(TGAHeader), 1, pTGAFIle);
        
        TGAColorMapSpec colorSpec;
        fread(&colorSpec, sizeof(TGAColorMapSpec), 1, pTGAFIle);
        
        TGAImageSpec imageSpec;
        fread(&imageSpec, sizeof(TGAImageSpec), 1, pTGAFIle);
        
        
        fclose(pTGAFIle);
        
        
        return true;
    }
    
    /*//------------------------------------------------------------
    // Purpose: Load a TGA file. 
    //------------------------------------------------------------
    bool CTGAFile::LoadTGA(const char *pszfilename)
    {
        if( !g_pFileSystem )
            return false;
        
        // File pointer to texture file
        FILE *fTGA = fopen(pszfilename, "rb");
        if(fTGA == NULL)
        {
            return false;
        }
        
        TGATypeHeader header;
        
        // Attempt to read 12 byte header from file
        if(fread(&header, sizeof(TGATypeHeader), 1, fTGA) == 0)
        {
            // Check to see if file is still open
            printf("Could not read tga file header for file %s\n", pszfilename);
            if(fTGA != NULL)
            {
                // If it is, close it
                fclose( fTGA );
            }
            
            // Exit function
            return false;
        }
        
        // See if header matches the predefined header of
        if(memcmp(uTGAcompare, &header, sizeof(header)) == 0)
        {
            // an Uncompressed TGA image
            // If so, jump to Uncompressed TGA loading code
            if(!LoadUncompressedTGA(pszfilename, fTGA))
            {
                return false;
            }
        }
        else if(memcmp(cTGAcompare, &header, sizeof(header)) == 0)
        {
            // See if header matches the predefined header of
            // an RLE compressed TGA image
            // If so, jump to Compressed TGA loading code
            if(!LoadCompressedTGA(pszfilename, fTGA))
            {
                return false;
            }
        }
        else
        {
            // If header matches neither type
            printf( "TGA file should be type 2 or type 10!" );
            fclose( fTGA );
            return false;
        }
        
        memset( texture->name, 0, MAX_TEX_NAME_LEN );
        int name_len = strlen( filename );
        
        if( name_len >= MAX_TEX_NAME_LEN )
            name_len = MAX_TEX_NAME_LEN-1;
        
        strncpy_s( texture->name, MAX_TEX_NAME_LEN, filename, name_len );
        
        // All went well, continue on
        return true;
    }
    
    //------------------------------------------------------------
    // Purpose: Load an uncompressed TGA file.
    //------------------------------------------------------------
    bool CTGAFile::LoadUncompressedTGA(const char *pszfilename, FILE *fTGA)
    {
        // Load an uncompressed TGA
        TGAHeader header;
        
        // Read TGA header
        if(fread(header, sizeof(TGAHeader), 1, fTGA) == 0)
        {
            // if file is still open
            printf( "Could not read tga info header!" );
            if(fTGA != NULL)					
            {
                fclose( fTGA );
            }
            
            // Exit file processing
            return false;
        }
        
        // Determine The TGA Width	(highbyte*256+lowbyte)
        m_iWidth  = tga.header[1] * 256 + tga.header[0];
        
        // Determine The TGA Height	(highbyte*256+lowbyte)
        m_iHeight = tga.header[3] * 256 + tga.header[2];
        
        // Determine the bits per pixel
        m_iBPP	= tga.header[4];
                
        // Make sure all information is valid
        if((m_iWidth <= 0) || (m_iHeight <= 0) ||
           ((m_iBPP != 24) && (m_iBPP != 32)))
        {
            // Check if file is still open
            printf( "Invalid tga texture information!" );
            if(fTGA != NULL)
            {
                // If so, close it
                fclose( fTGA );
            }
            
            // Stop processing file
            return false;
        }
        
        // If the BPP of the image is 24...
        if(m_iBPP == 24)
        {
            // Set Image type to GL_RGB
            texture->type	= GL_RGB;
        }
        else
        {
            // Set image type to GL_RGBA
            texture->type	= GL_RGBA;
        }
        
        // Compute the number of BYTES per pixel
        tga.bytesPerPixel	= (tga.Bpp / 8);
        
        // Compute the total amout ofmemory needed to store data
        tga.imageSize		= (tga.bytesPerPixel * tga.Width * tga.Height);
        
        // Allocate that much memory
        texture->imageData	= (GLubyte *)malloc(tga.imageSize);
        
        // If no space was allocated
        if(texture->imageData == NULL)
        {
            printf( "Could not allocate memory for tga data!" );
            g_pFileSystem->Close_File( fTGA );
            return false;
        }
        
        // Attempt to read image data
        if(fread(texture->imageData, 1, tga.imageSize, fTGA) != tga.imageSize)
        {
            // If imagedata has data in it
            printf( "Could not read image tga data!" );
            if(texture->imageData != NULL)
            {
                free(texture->imageData);
            }
            fclose( fTGA );
            return false;
        }
        
        // ByteSwap
        for(unsigned int cswap = 0; cswap < (int)tga.imageSize; cswap += tga.bytesPerPixel)
        {
            texture->imageData[cswap] ^= texture->imageData[cswap+2] ^=
            texture->imageData[cswap] ^= texture->imageData[cswap+2];
        }
        
        fclose( fTGA );
        return true;
    }
    
    //------------------------------------------------------------
    // Purpose: Load a compressed TGA file.
    //------------------------------------------------------------
    bool CTGAFile::LoadCompressedTGA(Texture * texture, const char * filename, FILE * fTGA)		// Load COMPRESSED TGAs
    {
        if(fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)					// Attempt to read header
        {
            WarningMsg( "Could not read tga info header!" );
            if(fTGA != NULL)													// If file is open
            {
                g_pFileSystem->Close_File( fTGA );								// Close it
            }
            return false;														// Return failed
        }
        
        texture->width  = tga.header[1] * 256 + tga.header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
        texture->height = tga.header[3] * 256 + tga.header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
        texture->bpp	= tga.header[4];										// Determine Bits Per Pixel
        tga.Width		= texture->width;										// Copy width to local structure
        tga.Height		= texture->height;										// Copy width to local structure
        tga.Bpp			= texture->bpp;											// Copy width to local structure
        
        if((texture->width <= 0) || (texture->height <= 0) || ((texture->bpp != 24) && (texture->bpp !=32)))	//Make sure all texture info is ok
        {
            WarningMsg( "Invalid tga texture information!" );
            if(fTGA != NULL)													// Check if file is open
            {
                g_pFileSystem->Close_File( fTGA );								// Ifit is, close it
            }
            return false;														// Return failed
        }
        
        if(texture->bpp == 24)													// If the BPP of the image is 24...
            texture->type	= GL_RGB;											// Set Image type to GL_RGB
        else																	// Else if its 32 BPP
            texture->type	= GL_RGBA;											// Set image type to GL_RGBA
        
        tga.bytesPerPixel	= (tga.Bpp / 8);									// Compute BYTES per pixel
        tga.imageSize		= (tga.bytesPerPixel * tga.Width * tga.Height);		// Compute amout of memory needed to store image
        texture->imageData	= (GLubyte *)malloc(tga.imageSize);					// Allocate that much memory
        
        if(texture->imageData == NULL)											// If it wasnt allocated correctly..
        {
            WarningMsg( "Could not allocate memory for tga image data!" );
            g_pFileSystem->Close_File( fTGA );									// Close file
            return false;														// Return failed
        }
        
        GLuint pixelcount	= tga.Height * tga.Width;							// Nuber of pixels in the image
        GLuint currentpixel	= 0;												// Current pixel being read
        GLuint currentbyte	= 0;												// Current byte
        GLubyte * colorbuffer = (GLubyte *)malloc(tga.bytesPerPixel);			// Storage for 1 pixel
        
        do
        {
            GLubyte chunkheader = 0;											// Storage for "chunk" header
            
            if(fread(&chunkheader, sizeof(GLubyte), 1, fTGA) == 0)				// Read in the 1 byte header
            {
                WarningMsg( "Could not read tga RLE header!" );
                if(fTGA != NULL)												// If file is open
                {
                    g_pFileSystem->Close_File( fTGA );							// Close file
                }
                if(texture->imageData != NULL)									// If there is stored image data
                {
                    free(texture->imageData);									// Delete image data
                }
                return false;													// Return failed
            }
            
            if(chunkheader < 128)												// If the ehader is < 128, it means the that is the number of RAW color packets minus 1
            {																	// that follow the header
                chunkheader++;													// add 1 to get number of following color values
                for(short counter = 0; counter < chunkheader; counter++)		// Read RAW color values
                {
                    if(fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel) // Try to read 1 pixel
                    {
                        WarningMsg( "Could not read tga image data!" );
                        
                        if(fTGA != NULL)													// See if file is open
                        {
                            g_pFileSystem->Close_File( fTGA );								// If so, close file
                        }
                        
                        if(colorbuffer != NULL)												// See if colorbuffer has data in it
                        {
                            free(colorbuffer);												// If so, delete it
                        }
                        
                        if(texture->imageData != NULL)										// See if there is stored Image data
                        {
                            free(texture->imageData);										// If so, delete it too
                        }
                        
                        return false;														// Return failed
                    }
                    // write to memory
                    texture->imageData[currentbyte		] = colorbuffer[2];				    // Flip R and B vcolor values around in the process
                    texture->imageData[currentbyte + 1	] = colorbuffer[1];
                    texture->imageData[currentbyte + 2	] = colorbuffer[0];
                    
                    if(tga.bytesPerPixel == 4)												// if its a 32 bpp image
                    {
                        texture->imageData[currentbyte + 3] = colorbuffer[3];				// copy the 4th byte
                    }
                    
                    currentbyte += tga.bytesPerPixel;										// Increase thecurrent byte by the number of bytes per pixel
                    currentpixel++;															// Increase current pixel by 1
                    
                    if(currentpixel > pixelcount)											// Make sure we havent read too many pixels
                    {
                        WarningMsg( "Too many pixels read from tga data, overflow!" );
                        
                        if(fTGA != NULL)													// If there is a file open
                        {
                            g_pFileSystem->Close_File( fTGA );								// Close file
                        }
                        
                        if(colorbuffer != NULL)												// If there is data in colorbuffer
                        {
                            free(colorbuffer);												// Delete it
                        }
                        
                        if(texture->imageData != NULL)										// If there is Image data
                        {
                            free(texture->imageData);										// delete it
                        }
                        
                        return false;														// Return failed
                    }
                }
            }
            else																			// chunkheader > 128 RLE data, next color reapeated chunkheader - 127 times
            {
                chunkheader -= 127;															// Subteact 127 to get rid of the ID bit
                if(fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel)		// Attempt to read following color values
                {
                    WarningMsg( "Could not read from tga file!" );
                    
                    if(fTGA != NULL)														// If thereis a file open
                    {
                        g_pFileSystem->Close_File( fTGA );									// Close it
                    }
                    
                    if(colorbuffer != NULL)													// If there is data in the colorbuffer
                    {
                        free(colorbuffer);													// delete it
                    }
                    
                    if(texture->imageData != NULL)											// If thereis image data
                    {
                        free(texture->imageData);											// delete it
                    }
                    
                    return false;															// return failed
                }
                
                for(short counter = 0; counter < chunkheader; counter++)					// copy the color into the image data as many times as dictated 
                {																			// by the header
                    texture->imageData[currentbyte		] = colorbuffer[2];					// switch R and B bytes areound while copying
                    texture->imageData[currentbyte + 1	] = colorbuffer[1];
                    texture->imageData[currentbyte + 2	] = colorbuffer[0];
                    
                    if(tga.bytesPerPixel == 4)												// If TGA images is 32 bpp
                    {
                        texture->imageData[currentbyte + 3] = colorbuffer[3];				// Copy 4th byte
                    }
                    
                    currentbyte += tga.bytesPerPixel;										// Increase current byte by the number of bytes per pixel
                    currentpixel++;															// Increase pixel count by 1
                    
                    if(currentpixel > pixelcount)											// Make sure we havent written too many pixels
                    {
                        WarningMsg( "Too many pixels read from tga data, overflow!" );
                        
                        if(fTGA != NULL)													// If there is a file open
                        {
                            g_pFileSystem->Close_File( fTGA );								// Close file
                        }	
                        
                        if(colorbuffer != NULL)												// If there is data in colorbuffer
                        {
                            free(colorbuffer);												// Delete it
                        }
                        
                        if(texture->imageData != NULL)										// If there is Image data
                        {
                            free(texture->imageData);										// delete it
                        }
                        
                        return false;														// Return failed
                    }
                }
            }
        }
        while(currentpixel < pixelcount);													// Loop while there are still pixels left
        
        // Free our holder.
        if( colorbuffer )
        {
            free( colorbuffer );
            colorbuffer = NULL;
        }
        
        g_pFileSystem->Close_File( fTGA );													// Close the file
        return true;																		// return success
    }*/
    
}
