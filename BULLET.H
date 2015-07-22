// Bullet.h: interface for the Bullet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BULLET_H__EC2170D3_378F_4916_AA04_986BF0AA0AE6__INCLUDED_)
#define AFX_BULLET_H__EC2170D3_378F_4916_AA04_986BF0AA0AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sprite.h"

class Bullet : public Sprite  
{
private:
	DIBitmap* bBitmap;	// Bullet Bitmap
	bool visible;		// want to show on the screen?
public:
	Bullet(int SPEED);
	
	void display();
	void setData(int x, int y, int dir);
	bool isVisible() const;
	void setNotVisible();
	void goAhead();
	bool collide(Sprite* sprite);
	bool collide(Bullet* bullet);
	virtual ~Bullet();

};

#endif // !defined(AFX_BULLET_H__EC2170D3_378F_4916_AA04_986BF0AA0AE6__INCLUDED_)
