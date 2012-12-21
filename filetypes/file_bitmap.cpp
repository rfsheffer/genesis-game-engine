

#include "stdafx.h"
#include "bitmap.h"

//-----------------------------------------------------------------------------
// Purpose: Swaps two pixels
//-----------------------------------------------------------------------------
void PixelSwap(bitmap_pixel_24 &pix1, bitmap_pixel_24 &pix2)
{
	byte temp;

	// red
	temp = pix1.r;
	pix1.r = pix2.r;
	pix2.r = temp;

	// green
	temp = pix1.g;
	pix1.g = pix2.g;
	pix2.g = temp;

	// blue
	temp = pix1.b;
	pix1.b = pix2.b;
	pix2.b = temp;
}

//-----------------------------------------------------------------------------
// Purpose: Loads a 24 bit color bitmap image
//-----------------------------------------------------------------------------
bool CBitmapImage::LoadBitmap(const char *pFileName)
{
	FILE *pFP = NULL;

	if(fopen_s(&pFP, pFileName, "rb"))
		return false;

	// Load the header information
	size_t headerSize = sizeof(bitmap_file_header);
	if(fread(&m_ImgHeader, 1, headerSize, pFP) != headerSize)
	{
		fclose(pFP);
		return false;
	}

	// Load the image information
	size_t infoSize = sizeof(bitmap_info_header);
	if(fread(&m_ImgInfo, 1, infoSize, pFP) != infoSize)
	{
		fclose(pFP);
		return false;
	}

	// TODO: Setup color pallets, reduce to 16 colors.
	if(m_ImgInfo.sNumPixelBits != 24)
	{
		fclose(pFP);
		return false;
	}

	// Position the stream to the start of the bitmap data
	fpos_t bitmapStart = m_ImgHeader.iBitMapOffset;

	rewind(pFP);
	if(fsetpos(pFP, &bitmapStart))
	{
		fclose(pFP);
		return false;
	}

	// Create the memory required to hold the bitmap data
	pBitmapData = new bitmap_pixel_24[m_ImgInfo.iHeight * m_ImgInfo.iWidth];
	if(!pBitmapData)
	{
		fclose(pFP);
		return false;
	}

	// Bitmap size in bytes
	int bitmapSize = m_ImgInfo.iHeight * m_ImgInfo.iWidth * sizeof(bitmap_pixel_24);

	// Lay the bitmap data onto the new memory.
	if(fread(pBitmapData, 1, bitmapSize, pFP) != bitmapSize)
	{
		fclose(pFP);
		return false;
	}

	// Bitmaps are flipped horizontally, so flip it back
	uint hoz_top = 0;
	uint hor_bot = m_ImgInfo.iHeight - 1;
	uint cur_top = 0, cur_bot = (hor_bot * m_ImgInfo.iWidth);
	uint cur_x;

	// Get the middle position, take into account non-divisible heights
	uint mid = (uint)floor(((float)hor_bot / 2));

	while(true)
	{
		// Swap the top and bottom.
		for(cur_x = 0; cur_x < m_ImgInfo.iWidth; cur_x++)
		{
			PixelSwap(pBitmapData[cur_top + cur_x], pBitmapData[cur_bot + cur_x]);
		}

		// even case check ( m_ImgInfo.iheight divisible by 2 )
		if(hoz_top == mid)
			break;

		// Shift top and bottom position horizontally
		hoz_top++;
		hor_bot--;

		// middle case check ( m_ImgInfo.iheight not divisible by 2 )
		if(hoz_top == hor_bot)
			break;

		// Shift the top and bottom array indices
		cur_top += m_ImgInfo.iWidth;
		cur_bot -= m_ImgInfo.iWidth;
	}

	fclose(pFP);

	// Debug output
#if(0)

	if(fopen_s(&pFP, "test_output.txt", "wb"))
		return false;

	int bitmap_pos = 0;

	for(uint i = 0; i < m_ImgInfo.iHeight; i++)
	{
		for(uint j = 0; j < m_ImgInfo.iWidth; j++)
		{
			// Write row
			if(pBitmapData[bitmap_pos].r == 255)
			{
				putc('.', pFP);
			}
			else
			{
				putc('#', pFP);
			}
			bitmap_pos++;
		}

		putc(13, pFP);
		putc(10, pFP);
	}

	fclose(pFP);

#endif

	return true;
}
