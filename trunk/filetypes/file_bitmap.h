#ifndef BITMAP_H
#define BITMAP_H

// For some reason Microsoft didn't data align this correctly, so I need to turn it off.
#include <pshpack2.h>
struct bitmap_file_header
{
	byte header[2];
	uint iFileSize;
	byte reserved[4];
	uint iBitMapOffset;
};
#include <poppack.h>

struct bitmap_info_header
{
	uint iInfoSize;			// specifies the size of the BITMAPINFOHEADER structure, in bytes.
	uint iWidth;			// specifies the width of the image, in pixels.
	uint iHeight;			// specifies the height of the image, in pixels.
	ushort sNumPlanes;		// specifies the number of planes of the target device, must be set to zero.
	ushort sNumPixelBits;	// specifies the number of bits per pixel.
	uint iCompression;		// Specifies the type of compression, usually set to zero (no compression).
	uint iImgDataSize;		// specifies the size of the image data, in bytes. If there is no compression, it is valid to set this member to zero.
	uint iXPixPerMeter;		// specifies the the horizontal pixels per meter on the designated targer device, usually set to zero.
	uint iYPixPerMeter;		// specifies the the vertical pixels per meter on the designated targer device, usually set to zero.
	uint iNumColors;		// specifies the number of colors used in the bitmap, if set to zero the number of colors is calculated using the sNumPixelBits member.
	uint iNumImpColors;		// specifies the number of color that are 'important' for the bitmap, if set to zero, all colors are important.
};

struct bitmap_pixel_24
{
	byte	r;
	byte	g;
	byte	b;
};

class CBitmapImage
{
public:

	CBitmapImage()
	{
		pBitmapData = NULL;
	}

	~CBitmapImage()
	{
		if(pBitmapData)
		{
			delete [] pBitmapData;
			pBitmapData = NULL;
		}
	}

	bool LoadBitmap(const char *pFileName);

	bitmap_file_header m_ImgHeader;
	bitmap_info_header m_ImgInfo;

	// The actual pixels
	bitmap_pixel_24 *pBitmapData;
};


#endif // BITMAP_H