// DIBitmap.cpp: implementation of the DIBitmap class.
//
//////////////////////////////////////////////////////////////////////

#include "DIBitmap.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DIBitmap::DIBitmap(const char *fileName,GLubyte r,GLubyte g,GLubyte b)
{
	_bitmap = 0;
	_bitMapInfo = 0;
	setLimpidColor(r,g,b);
	loadBitmapA(fileName);
}

DIBitmap::DIBitmap(const char *fileName) : _bitmap(0), _bitMapInfo(0)
{
	loadBitmap(fileName);
}

DIBitmap::~DIBitmap()
{

}

void DIBitmap::loadBitmap(const char *fileName)
{
	_bitmap = LoadDIBitmap(fileName,&_bitMapInfo);
}

void DIBitmap::loadBitmapA(const char *fileName)
{
	if(_bitmap) free(_bitmap);
	if(_bitMapInfo) free(_bitMapInfo);
	_bitmap = LoadRGBA(fileName,&_bitMapInfo);
}
GLubyte *                          /* O - Bitmap data */
DIBitmap::LoadDIBitmap(const char *filename, /* I - File to load */
             BITMAPINFO **info)    /* O - Bitmap information */
    {
    FILE             *fp;          /* Open file pointer */
    GLubyte          *bits;        /* Bitmap pixel bits */
    int              bitsize;      /* Size of bitmap */
    int              infosize;     /* Size of header information */
    BITMAPFILEHEADER header;       /* File header */


    /* Try opening the file; use "rb" mode to read this *binary* file. */
    if ((fp = fopen(filename, "rb")) == NULL)
        return (NULL);

    /* Read the file header and any following bitmap information... */
    if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
        {
        /* Couldn't read the file header - return NULL... */
	fclose(fp);
        return (NULL);
        }

    if (header.bfType != 'MB')	/* Check for BM reversed... */
        {
        /* Not a bitmap file - return NULL... */
        fclose(fp);
        return (NULL);
        }

    infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
    if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
        {
        /* Couldn't allocate memory for bitmap info - return NULL... */
        fclose(fp);
        return (NULL);
        }

    if (fread(*info, 1, infosize, fp) < (unsigned)infosize)
        {
        /* Couldn't read the bitmap header - return NULL... */
        free(*info);
        fclose(fp);
        return (NULL);
        }

    /* Now that we have all the header info read in, allocate memory for *
     * the bitmap and read *it* in...                                    */
    if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
        bitsize = ((*info)->bmiHeader.biWidth *
                   (*info)->bmiHeader.biBitCount + 7) / 8 *
  	           abs((*info)->bmiHeader.biHeight);

    if ((bits = (unsigned char *)malloc(bitsize)) == NULL)
        {
        /* Couldn't allocate memory - return NULL! */
        free(*info);
        fclose(fp);
        return (NULL);
        }

    if (fread(bits, 1, bitsize, fp) < (unsigned)bitsize)
        {
        /* Couldn't read bitmap - free memory and return NULL! */
        free(*info);
        free(bits);
        fclose(fp);
        return (NULL);
        }

    /* OK, everything went fine - return the allocated bitmap... */
    fclose(fp);
    return (bits);
 }

void DIBitmap::drawPixelsA(int left,int bottom)
{
	glRasterPos2f(left,bottom);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDrawPixels(_bitMapInfo->bmiHeader.biWidth,
                 _bitMapInfo->bmiHeader.biHeight,
                 GL_RGBA, GL_UNSIGNED_BYTE, _bitmap);
	glDisable(GL_BLEND);
}

void DIBitmap::drawPixels(int left,int bottom)
{
	glRasterPos2f(left,bottom);
    glDrawPixels(_bitMapInfo->bmiHeader.biWidth,
                 _bitMapInfo->bmiHeader.biHeight,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, _bitmap);
}

/*DIBitmap::DIBitmap()
{
	_bitmap = 0;
	_bitMapInfo = 0;
}*/

void DIBitmap::operator =(DIBitmap)
{

}

GLubyte * DIBitmap::LoadRGBA(const char *filename, BITMAPINFO **info)
{
    GLubyte    *bgr;           /* BGR bitmap data */
    GLubyte    *rgba;          /* RGBA bitmap data */
    int        x, y;           /* Looping vars */
    int        length;         /* Length of scanline */
    GLubyte    *bgr_ptr;       /* Pointer into BGR data */
    GLubyte    *rgba_ptr;      /* Pointer into RGBA data */

    bgr    = LoadDIBitmap(filename, info);
    rgba   = (unsigned char *) malloc((*info)->bmiHeader.biWidth *
                    (*info)->bmiHeader.biHeight * 4);
    length = ((*info)->bmiHeader.biWidth * 3 + 3) & ~3;

    for (y = 0; y < (*info)->bmiHeader.biHeight; y ++)
        {
        bgr_ptr  = bgr + y * length;
        rgba_ptr = rgba + y * (*info)->bmiHeader.biWidth * 4;

        for (x = 0; x < (*info)->bmiHeader.biWidth; x ++, bgr_ptr += 3, rgba_ptr += 4)
            {
				rgba_ptr[0] = bgr_ptr[2];
				rgba_ptr[1] = bgr_ptr[1];
				rgba_ptr[2] = bgr_ptr[0];
				if(rgba_ptr[0]==_limpidColor[0] && 
				   rgba_ptr[1]==_limpidColor[1] && 
				   rgba_ptr[2]==_limpidColor[2])
				   rgba_ptr[3] = 0;
				else rgba_ptr[3] = 255;
            }
        }
    free(bgr);
    return (rgba);
}

void DIBitmap::setLimpidColor(GLubyte r, GLubyte g, GLubyte b)
{
	_limpidColor[0] = r;
	_limpidColor[1] = g;
	_limpidColor[2] = b;
}
