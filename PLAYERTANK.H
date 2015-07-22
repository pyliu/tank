// Atank.h: interface for the Playertank class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATANK_H__C9638653_2AA7_4C3A_A88E_8628DB750DEA__INCLUDED_)
#define AFX_ATANK_H__C9638653_2AA7_4C3A_A88E_8628DB750DEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////

#include "Sprite.h"

class PlayerTank : public Sprite  
{
private:
	DIBitmap* ptBitmap[4];	// Player Tank Bitmap
	DIBitmap* dieBitmap[2];	// dead bitmap
	Bullet* bullet;
	bool ifdead;
	int dead_frame_count;	// 顯示dead的frame數
	int life;
public:
	PlayerTank();
	
	void display();	
	Bullet* getBullet() const;	// send to Controller
	bool getIfdead() const;
	int getLife() const;
	void setDead();
	void setDefaultPosition();
	void shoot();
	void reset();
	void resetAll();

	// bonus life
	void bonus(int life_count);
	virtual ~PlayerTank();
};

//////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_ATANK_H__C9638653_2AA7_4C3A_A88E_8628DB750DEA__INCLUDED_)
