// Wall.h: interface for the Wall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WALL_H__BE2A307E_6330_4277_910E_FD49D86E1ECE__INCLUDED_)
#define AFX_WALL_H__BE2A307E_6330_4277_910E_FD49D86E1ECE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sprite.h"

class Wall : public Sprite  
{
private:
	DIBitmap* wallBitmap;
public:
	Wall(int x, int y);

	void display();

	virtual ~Wall();

};

#endif // !defined(AFX_WALL_H__BE2A307E_6330_4277_910E_FD49D86E1ECE__INCLUDED_)
