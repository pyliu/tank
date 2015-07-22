// PlayerTank.cpp: implementation of the Atank class.
//
//////////////////////////////////////////////////////////////////////

#include "data_declaration.h"
#include "PlayerTank.h"
#include "Bullet.h"
#include "DIBitmap.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PlayerTank::PlayerTank()
{ 
	speed = 4;
	bullet = new Bullet(8);
	ifdead = false;
	dead_frame_count = 10;
	life = 3;
	pos_y = TILE_HEIGHT*(BOARD_HEIGHT-1);
	//id = PTANK;
	ptBitmap[0] = new DIBitmap(pNORTHBITMAP, 0, 0, 0);
	ptBitmap[1] = new DIBitmap(pEASTBITMAP, 0, 0, 0);
	ptBitmap[2] = new DIBitmap(pSOUTHBITMAP, 0, 0, 0);
	ptBitmap[3] = new DIBitmap(pWESTBITMAP, 0, 0, 0);
	dieBitmap[0] = new DIBitmap(DIEBITMAP1, 0, 0, 0);
	dieBitmap[1] = new DIBitmap(DIEBITMAP2, 0, 0, 0);
}

PlayerTank::~PlayerTank()
{
	delete ptBitmap[0];
	delete ptBitmap[1];
	delete ptBitmap[2];
	delete ptBitmap[3];
	delete bullet;
	delete dieBitmap[0];
	delete dieBitmap[1];
}

//////////////////////////////////////////////////////////////////////
// show Playertank on to screen
//////////////////////////////////////////////////////////////////////

void
PlayerTank::display()
{	
	if (!ifdead)
	{
		switch(direction)
		{
			case NORTH:
				ptBitmap[0]->drawPixelsA(pos_x, pos_y);
				break;
			case EAST:
				ptBitmap[1]->drawPixelsA(pos_x, pos_y);
				break;
			case SOUTH:
				ptBitmap[2]->drawPixelsA(pos_x, pos_y);
				break;
			case WEST:
				ptBitmap[3]->drawPixelsA(pos_x, pos_y);
				break;
		}
	} else
	{
		if (dead_frame_count > 0)
		{
			// show dead animation
			if (dead_frame_count%2 == 0)
				dieBitmap[0]->drawPixelsA(pos_x, pos_y);
			else
				dieBitmap[1]->drawPixelsA(pos_x, pos_y);

			--dead_frame_count;
			if (dead_frame_count == 0)
				reset();
		}
	}
	if ( bullet->isVisible() )
			bullet->display();
}

//////////////////////////////////////////////////////////////////////
// get and set data
//////////////////////////////////////////////////////////////////////

bool
PlayerTank::getIfdead() const
{ return ifdead; }

Bullet*
PlayerTank::getBullet() const
{ return bullet; }

int
PlayerTank::getLife() const
{ return life; }

void
PlayerTank::setDead()
{
	if (!ifdead)
	{
		PlaySound(DEADWAV, 0, SND_ASYNC);
		ifdead = true;
		--life;
	} else if (life == 0)
	{	// 把坦克移出玩的區域
		pos_x = -TILE_WIDTH*2;
		pos_y = -TILE_HEIGHT*2;
	}
}

void
PlayerTank::setDefaultPosition()
{
	pos_x = 0;
	pos_y = TILE_HEIGHT*(BOARD_HEIGHT-1);
}

void
PlayerTank::reset()
{
	if (life != 0)
	{
		PlaySound(REMINDERWAV, 0, SND_ASYNC);
		ifdead = false;
		dead_frame_count = 10;
		/*
		int pos_key = rand() % 4;
		switch(pos_key)
		{
		case 1:	// 左上角
			pos_x = 0;
			pos_y = TILE_HEIGHT*(BOARD_HEIGHT-1);
			break;
		case 2:	// 左下角
			pos_x = 0;
			pos_y = 0;
			break;
		case 3:	// 右上角
			pos_x = TILE_WIDTH*(BOARD_WIDTH-1);
			pos_y = TILE_HEIGHT*(BOARD_HEIGHT-1);
			break;
		case 4:	// 右下角
			pos_x = TILE_WIDTH*(BOARD_WIDTH-1);;
			pos_y = 0;
			break;
		}
		*/
	}
}

void
PlayerTank::resetAll()
{
	life = 3;
	ifdead = false;
	dead_frame_count = 10;
	pos_x = 0;
	pos_y = TILE_HEIGHT*(BOARD_HEIGHT-1);
}

//////////////////////////////////////////////////////////////////////
// shoot bullet
//////////////////////////////////////////////////////////////////////

void
PlayerTank::shoot()
{
	if ( !bullet->isVisible() )
	{
		bullet->setData(pos_x, pos_y, direction);
		PlaySound(SHOOTWAV, NULL, SND_ASYNC);
	}
}

//////////////////////////////////////////////////////////////////////
// add life
//////////////////////////////////////////////////////////////////////

void
PlayerTank::bonus(int life_count)
{
	life += life_count;
}