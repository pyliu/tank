// Sprite.h: interface for the Sprite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRITE_H__33BA4D71_2B54_42AA_A04F_FA98359782BE__INCLUDED_)
#define AFX_SPRITE_H__33BA4D71_2B54_42AA_A04F_FA98359782BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////

class DIBitmap;
class Bullet;

class Sprite  
{
protected:
	int pos_x, pos_y, speed;	// count in pixels
	int direction;
public:
	
	Sprite();
	virtual void display();	// Show Sprite on to screen

	virtual void MoveUp();
	virtual void MoveDown();
	virtual void MoveLeft();
	virtual void MoveRight();

	virtual int getPos_x() const;
	virtual int getPos_y() const;
	virtual int getSpeed() const;
	virtual int getDirection() const;
	virtual void setDirection(int DIRECTION);
	virtual void setOtherDirecton();

	virtual bool collide(Sprite* sprite);	//偵測兩物體是否碰撞

	virtual ~Sprite();	// if we use virtual function we should declare virtual destructor
};

//////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_SPRITE_H__33BA4D71_2B54_42AA_A04F_FA98359782BE__INCLUDED_)
