// Sprite.cpp: implementation of the Sprite class.
//
//////////////////////////////////////////////////////////////////////
#include "data_declaration.h"
#include "Sprite.h"
#include <cstdlib>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Sprite::Sprite() : pos_x(0), pos_y(0), speed(4), direction(rand() % 4)
{}

Sprite::~Sprite()
{}

//////////////////////////////////////////////////////////////////////
// get the data
//////////////////////////////////////////////////////////////////////

inline int
Sprite::getPos_x() const
{ return pos_x; }

inline int
Sprite::getPos_y() const
{ return pos_y; }

inline int
Sprite::getSpeed() const
{ return speed; }

inline int
Sprite::getDirection() const
{ return direction; }

/*inline int
Sprite::getId() const
{ return id; }
*/
void
Sprite::setDirection(int DIRECTION)
{
	direction = DIRECTION;
}

void
Sprite::setOtherDirecton()
{}

//////////////////////////////////////////////////////////////////////
// Move PlayerTank in 4 direction
//////////////////////////////////////////////////////////////////////

void
Sprite::MoveDown()
{
	direction = SOUTH;
	pos_y -= speed;
	// 檢查以確定移動不會超出螢幕下面
	if( pos_y < 0 )
	{
		//direction = NORTH;
		direction = rand() % 4;
		pos_y = 0;
	}
}

void
Sprite::MoveLeft()
{
	direction = WEST;
	pos_x -= speed;
	// 檢查以確定移動不會超出螢幕左邊
	if( pos_x < 0)
	{
		//direction = EAST;
		direction = rand() % 4;
		pos_x = 0;
	}
}

void
Sprite::MoveRight()
{
	direction = EAST;
	pos_x += speed;
	// 檢查以確定移動不會超出螢幕右邊
	if( (pos_x + TILE_WIDTH) > (TILE_WIDTH * BOARD_WIDTH) )
	{
		//direction = WEST;
		direction = rand() % 4;
		pos_x = TILE_WIDTH * BOARD_WIDTH - TILE_WIDTH;
	}
}

void
Sprite::MoveUp()
{
	direction = NORTH;
	pos_y += speed;
	// 檢查以確定移動不會超出螢幕上面
	if( (pos_y + TILE_HEIGHT) > (TILE_HEIGHT * BOARD_HEIGHT) )
	{
		//direction = SOUTH;
		direction = rand() % 4;
		pos_y = TILE_HEIGHT * BOARD_HEIGHT - TILE_HEIGHT;
	}
}

//////////////////////////////////////////////////////////////////////
// display() do nothing
//////////////////////////////////////////////////////////////////////

void
Sprite::display()
{}

//////////////////////////////////////////////////////////////////////
// 偵測是否和另一個物體有碰撞
//////////////////////////////////////////////////////////////////////

bool
Sprite::collide(Sprite* sprite)
{
	bool flag = false;

	int self_x = getPos_x();
	int self_y = getPos_y();
	int other_x = sprite->getPos_x();
	int other_y = sprite->getPos_y();
	
	int distance_x = 0;
	int distance_y = 0;
	
	if (self_x >= other_x)
		distance_x = self_x - (other_x+TILE_WIDTH);
	else
		distance_x = other_x - (self_x+TILE_WIDTH);

	if (self_y >= other_y)
		distance_y = self_y - (other_y+TILE_HEIGHT);
	else
		distance_y = other_y - (self_y+TILE_HEIGHT);
	if (distance_x < 0 && distance_y < 0)
			flag = true;

	return flag;
}