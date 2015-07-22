// EnemyTank.cpp: implementation of the EnemyTank class.
//
//////////////////////////////////////////////////////////////////////

#include "data_declaration.h"
#include "EnemyTank.h"
#include "Bullet.h"
#include "DIBitmap.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyTank::EnemyTank(int x, int y, int sp)
{ 
	speed = sp;
	direction = rand() % 4;
	pos_x = x;
	pos_y = y;
	dead_frame_count = 10;
	ifdead = false;
	bullet = new Bullet(8);
	//id = ETANK;

	etBitmap[0] = new DIBitmap(eNORTHBITMAP, 0, 0, 0);
	etBitmap[1] = new DIBitmap(eEASTBITMAP, 0, 0, 0);
	etBitmap[2] = new DIBitmap(eSOUTHBITMAP, 0, 0, 0);
	etBitmap[3] = new DIBitmap(eWESTBITMAP, 0, 0, 0);
	dieBitmap[0] = new DIBitmap(DIEBITMAP1, 0, 0, 0);
	dieBitmap[1] = new DIBitmap(DIEBITMAP2, 0, 0, 0);
}

EnemyTank::~EnemyTank()
{
	delete etBitmap[0];
	delete etBitmap[1];
	delete etBitmap[2];
	delete etBitmap[3];
	delete bullet;
	delete dieBitmap[0];
	delete dieBitmap[1];
}

//////////////////////////////////////////////////////////////////////
// show EnemyTank on to screen
//////////////////////////////////////////////////////////////////////

void
EnemyTank::display()
{	
	if (!ifdead)
	{
		switch(direction)
		{
			case NORTH:
				etBitmap[0]->drawPixelsA(pos_x, pos_y);
				break;
			case EAST:
				etBitmap[1]->drawPixelsA(pos_x, pos_y);
				break;
			case SOUTH:
				etBitmap[2]->drawPixelsA(pos_x, pos_y);
				break;
			case WEST:
				etBitmap[3]->drawPixelsA(pos_x, pos_y);
				break;
		}
	} else
	{
		if (dead_frame_count != 0)
		{
			// 顯示爆炸的畫面
			if (dead_frame_count%2 == 0)
				dieBitmap[0]->drawPixelsA(pos_x, pos_y);
			else
				dieBitmap[1]->drawPixelsA(pos_x, pos_y);
			--dead_frame_count;
			//dieBitmap->drawPixels(pos_x, pos_y);	// 
		} else
		{
			// enemy tank move out the screen
			pos_x = -(TILE_WIDTH*2);
			pos_y = -(TILE_HEIGHT*2);
		}
	}
	if ( bullet->isVisible() )
		bullet->display();
}

//////////////////////////////////////////////////////////////////////
// get datas
//////////////////////////////////////////////////////////////////////

Bullet*
EnemyTank::getBullet() const
{ return bullet; }

bool
EnemyTank::getIfdead() const
{ return ifdead; }

int
EnemyTank::getDead_frame_count() const
{ return dead_frame_count; }
//////////////////////////////////////////////////////////////////////
// set data
//////////////////////////////////////////////////////////////////////

void
EnemyTank::setOtherDirecton()
{
	int temp = rand() % 4;
	int reverse_direction = (direction + 2) % 4;
	//設定會往目前行進方向的垂直方向作改變
	while (direction == temp || reverse_direction == temp)
		temp = rand() % 4;
	direction = temp;
}

void
EnemyTank::setDead()
{
	ifdead = true;
	PlaySound(DEADWAV, 0, SND_ASYNC);
}
//////////////////////////////////////////////////////////////////////
// shoot bullet
//////////////////////////////////////////////////////////////////////

void
EnemyTank::shoot()
{
	if ( !bullet->isVisible() )
		bullet->setData(pos_x, pos_y, direction);
}