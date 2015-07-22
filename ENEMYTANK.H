// EnemyTank.h: interface for the EnemyTank class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYTANK_H__40551814_D06C_44A1_B762_DF0AA4AAF7CC__INCLUDED_)
#define AFX_ENEMYTANK_H__40551814_D06C_44A1_B762_DF0AA4AAF7CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sprite.h"

class EnemyTank : public Sprite  
{
private:
	DIBitmap* etBitmap[4];	// Enemy Tank Bitmap
	DIBitmap* dieBitmap[2];
	Bullet* bullet;
	bool ifdead;
	int dead_frame_count;
public:
	EnemyTank(int x, int y, int sp);	// 出現在指定的位置(x, y, speed)
	
	void display();	
	void setOtherDirecton();
	Bullet* getBullet() const;	// send to Controller in controller's ctor
	void setDead();
	bool getIfdead() const;
	int getDead_frame_count() const;
	void shoot();
	
	virtual ~EnemyTank();

};

#endif // !defined(AFX_ENEMYTANK_H__40551814_D06C_44A1_B762_DF0AA4AAF7CC__INCLUDED_)
