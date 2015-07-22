// DIBitmap.h: interface for the DIBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIBITMAP_H__30C71131_C693_427B_A8C2_723D0DF4A136__INCLUDED_)
#define AFX_DIBITMAP_H__30C71131_C693_427B_A8C2_723D0DF4A136__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bitmap.h"
#include <cstdio>
#include <cstdlib>
#include <cerrno>

class DIBitmap  
{
public:
	void drawPixelsA(int left,int bottom);
	void drawPixels(int left,int bottom);
	DIBitmap(const char *fileName,GLubyte r,GLubyte g,GLubyte b);	// �n�ϥγz����
	DIBitmap(const char *fileName);	// ���ϥγz����
	virtual ~DIBitmap();
protected:
	void loadBitmap(const char *fileName);	// ���ϥγz���⪺ctor�I�s
	void loadBitmapA(const char *fileName);	// �ϥγz���⪺ctor�I�s
	void setLimpidColor(GLubyte r,GLubyte g,GLubyte b);	// �ϥγz���⪺ctor�I�s
	GLubyte * LoadDIBitmap(const char *filename,BITMAPINFO **info);
	GLubyte * LoadRGBA(const char *filename,BITMAPINFO **info);
private:
	void operator=(DIBitmap);
	GLubyte * _bitmap;
	BITMAPINFO *_bitMapInfo;
	GLubyte _limpidColor[3];
	
};

#endif // !defined(AFX_DIBITMAP_H__30C71131_C693_427B_A8C2_723D0DF4A136__INCLUDED_)