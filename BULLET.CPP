// Bullet.cpp: implementation of the Bullet class.
//
//////////////////////////////////////////////////////////////////////

#include "data_declaration.h"
#include "Bullet.h"
#include "DIBitmap.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Bullet::Bullet(int SPEED)
{
	speed = SPEED;
	visible = false;
	bBitmap = new DIBitmap(BULLETBITMAP);
}

Bullet::~Bullet()
{
	delete bBitmap;
}

//////////////////////////////////////////////////////////////////////
// display bullet on the screen
//////////////////////////////////////////////////////////////////////

void
Bullet::display()
{
	bBitmap->drawPixels(pos_x, pos_y);
}

//////////////////////////////////////////////////////////////////////
// set data
//////////////////////////////////////////////////////////////////////

void
Bullet::setData(int x, int y, int dir)
{
	visible = true;
	direction = dir;
	switch(direction)
	{
	case NORTH:
		pos_x = x+TILE_WIDTH/2-1;
		pos_y = y+TILE_HEIGHT;
		break;
	case EAST:
		pos_x = x+TILE_WIDTH;
		pos_y = y+TILE_HEIGHT/2-1;
		break;
	case SOUTH:
		pos_x = x+TILE_WIDTH/2-1;
		pos_y = y-2;
		break;
	case WEST:
		pos_x = x-2;
		pos_y = y+TILE_HEIGHT/2-1;
		break;
	}
}

void
Bullet::setNotVisible()
{
	pos_x = -3;
	pos_y = -3;
	visible = false;
}
//////////////////////////////////////////////////////////////////////
// bullet next step
//////////////////////////////////////////////////////////////////////

void
Bullet::goAhead()
{
	switch(direction)
	{
		case NORTH:
			if (visible)
			{
				pos_y += speed;
				if (pos_y > TILE_HEIGHT*BOARD_HEIGHT-2)
				{
					pos_x = -3;
					pos_y = -3;
					visible = false;
				}
			}
			break;
		case EAST:
			if (visible)
			{
				pos_x += speed;
				if (pos_x > TILE_WIDTH*BOARD_WIDTH-2)
				{
					pos_x = -3;
					pos_y = -3;
					visible = false;
				}
			}
			break;
		case SOUTH:
			if (visible)
			{
				pos_y -= speed;
				if (pos_y <0 )
				{
					pos_x = -3;
					pos_y = -3;
					visible = false;
				}
			}
			break;
		case WEST:
			if (visible)
			{
				pos_x -= speed;
				if (pos_x < 0)
				{
					pos_x = -3;
					pos_y = -3;
					visible = false;
				}
			}
			break;
	}
}

//////////////////////////////////////////////////////////////////////
// get data
//////////////////////////////////////////////////////////////////////

bool
Bullet::isVisible() const
{ return visible; }

//////////////////////////////////////////////////////////////////////
// collision detect
//////////////////////////////////////////////////////////////////////

bool
Bullet::collide(Sprite* sprite)
{
	bool flag = false;

	int self_x = getPos_x();
	int self_y = getPos_y();
	int other_x = sprite->getPos_x();
	int other_y = sprite->getPos_y();

	int distance_x = 0;
	int distance_y = 0;
	// bullet's pixel is 3x3
	if (self_x >= other_x)
		distance_x = self_x - (other_x+TILE_WIDTH);
	else
		distance_x = other_x - (self_x+3);

	if (self_y >= other_y)
		distance_y = self_y - (other_y+TILE_HEIGHT);
	else
		distance_y = other_y - (self_y+3);
	if (distance_x < 0 && distance_y < 0)
			flag = true;
	
	return flag;
}


bool
Bullet::collide(Bullet* bullet)
{
	bool flag = false;

	int self_x = getPos_x();
	int self_y = getPos_y();
	int other_x = bullet->getPos_x();
	int other_y = bullet->getPos_y();

	int distance_x = 0;
	int distance_y = 0;
	// bullet's pixel is 3x3
	if (self_x >= other_x)
		distance_x = self_x - (other_x+8);	// bullet speed is 8 more than their width and height
	else									// so place their speed other than their width and height
		distance_x = other_x - (self_x+8);

	if (self_y >= other_y)
		distance_y = self_y - (other_y+8);
	else
		distance_y = other_y - (self_y+8);
	if (distance_x < 0 && distance_y < 0)
			flag = true;
	
	return flag;
}
