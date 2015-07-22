// controller.cpp: implementation of the Controller class.
//
//////////////////////////////////////////////////////////////////////

#include "data_declaration.h"
#include "controller.h"
#include "DIBitmap.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Wall.h"
#include "Bullet.h"
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

//////////////////////////////////////////////////////////////////////
// display functor
//////////////////////////////////////////////////////////////////////

class Display {
public:
	void operator()(Sprite* obj) { obj->display(); }
};

/*
void Display(Sprite* obj)
{
	obj->display();
}
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Controller::Controller() : enemy_dead_count(0), gameover_sound_count(1),
 stage_title_count(60), stage_flag(1), over_clear_key(90)
{
	goBitmap = new DIBitmap(GOBITMAP, 0, 0, 0);
	scBitmap = new DIBitmap(SCBITMAP, 0, 0, 0);
	st1Bitmap = new DIBitmap(STAGE1START, 0, 0, 0);
	st2Bitmap = new DIBitmap(STAGE2START, 0, 0, 0);
	st3Bitmap = new DIBitmap(STAGE3START, 0, 0, 0);
	floorBitmap = new DIBitmap(FLOORBITMAP);
	PT = new PlayerTank;	//把playertank加入方便管理
	
	loadStage1();
}

Controller::~Controller()
{
	delete PT;
	enemyObj.clear();
	wallObj.clear();
	delete goBitmap;
	delete scBitmap;
	delete st1Bitmap;
	delete st2Bitmap;
	delete st3Bitmap;
	delete floorBitmap;
}

//////////////////////////////////////////////////////////////////////
// display all object on the screen
//////////////////////////////////////////////////////////////////////

void
Controller::display()
{
	showFloor();
	// 第一層先畫wall
	showWall();
	// 第二層畫enemy坦克
	showTank();

	showGameMessage();
}

//////////////////////////////////////////////////////////////////////
// EnemyTank AI
//////////////////////////////////////////////////////////////////////

void
Controller::enemyAI()
{
	playerMove();
	enemyMove();
	bulletMove();
	checkPlayerBullet();
	checkEnemyBullet();
}

//////////////////////////////////////////////////////////////////////
// player and enemy move
//////////////////////////////////////////////////////////////////////

void
Controller::playerMove()
{
	if ( !PT->getIfdead() )
	{
		if (KeyBuffer.size() != 0)
		{
			switch( KeyBuffer.front() )
			{
			case GLUT_KEY_RIGHT:
				PT->MoveRight();
				PT->setDirection(EAST);	//防止到螢幕邊緣時會亂跳
				//collision detect
				if ( isTank_PT() )
				{
					PT->MoveLeft();
					PT->setDirection(EAST);
				} else if ( isWall(PT) )
				{
					PT->MoveLeft();
					PT->setDirection(EAST);
				}
				break;
			case GLUT_KEY_UP:
				PT->MoveUp();
				PT->setDirection(NORTH);
				if ( isTank_PT() )
				{
					PT->MoveDown();
					PT->setDirection(NORTH);
				} else if ( isWall(PT) )
				{
					PT->MoveDown();
					PT->setDirection(NORTH);
				}
				break;
			case GLUT_KEY_LEFT:
				PT->MoveLeft();
				PT->setDirection(WEST);
				if ( isTank_PT() )
				{
					PT->MoveRight();
					PT->setDirection(WEST);
				} else if ( isWall(PT) )
				{
					PT->MoveRight();
					PT->setDirection(WEST);
				}
				break;
			case GLUT_KEY_DOWN:
				PT->MoveDown();
				PT->setDirection(SOUTH);
				if ( isTank_PT() )
				{
					PT->MoveUp();
					PT->setDirection(SOUTH);
				} else if ( isWall(PT) )
				{
					PT->MoveUp();
					PT->setDirection(SOUTH);
				}
				break;
			case VK_SPACE:
				PT->shoot();
				break;
			case GLUT_KEY_F1:
				PT->bonus(3);
				break;
			}
			KeyBuffer.pop();
	}
	} else
		while (KeyBuffer.size() != 0)
			KeyBuffer.pop();	// clear buffer
}

void
Controller::enemyMove()
{
	int eai = 0;			// enemy ai condition variable
	int dir = 0;

	for (int i = 0; i < enemyObj.size(); ++i)
	{	
		if ( !enemyObj[i]->getIfdead() )
		{
			eai = rand() % 100;
			if (eai < 2)
			{
				//朝player行進(2%)
				switch(eai)
				{
				case 0:
					// enemy在player的右邊
					if ( enemyObj[i]->getPos_x() > PT->getPos_x() )
					{
						enemyObj[i]->MoveLeft();	//西

						if ( isTank(enemyObj[i]) || isWall(enemyObj[i]) )
						{
							enemyObj[i]->MoveRight();
							enemyObj[i]->setOtherDirecton();
						}
						enemyObj[i]->shoot();
					} else
					{
						enemyObj[i]->MoveRight();	//東
						
						if ( isTank(enemyObj[i]) || isWall(enemyObj[i]) )
						{
							enemyObj[i]->MoveLeft();
							enemyObj[i]->setOtherDirecton();
						}
						enemyObj[i]->shoot();
					}
					break;
				case 1:
					if ( enemyObj[i]->getPos_y() > PT->getPos_y() )
					{
						enemyObj[i]->MoveDown();	//南
						
						if ( isTank(enemyObj[i]) || isWall(enemyObj[i]) )
						{
							enemyObj[i]->MoveUp();
							enemyObj[i]->setOtherDirecton();
						}
						enemyObj[i]->shoot();
					} else
					{
						enemyObj[i]->MoveUp();	//北
						
						if ( isTank(enemyObj[i]) || isWall(enemyObj[i]) )
						{
							enemyObj[i]->MoveDown();
							enemyObj[i]->setOtherDirecton();
						}
						enemyObj[i]->shoot();
					}
					break;
				}
			} else
			{
				//enemy維持原方向行進(98%)
				switch( enemyObj[i]->getDirection() )
				{
				case NORTH:
					enemyObj[i]->MoveUp();
					
					if ( isTank(enemyObj[i]) || isWall(enemyObj[i]) )
					{
						enemyObj[i]->MoveDown();
						enemyObj[i]->setOtherDirecton();
					}
					break;
				case EAST:
					enemyObj[i]->MoveRight();
					
					if ( isTank(enemyObj[i]) || isWall(enemyObj[i]) )
					{
						enemyObj[i]->MoveLeft();
						enemyObj[i]->setOtherDirecton();
					}
					break;
				case SOUTH:
					enemyObj[i]->MoveDown();
					
					if ( isTank(enemyObj[i]) || isWall(enemyObj[i]) )
					{
						enemyObj[i]->MoveUp();
						enemyObj[i]->setOtherDirecton();
					}
					break;
				case WEST:
					enemyObj[i]->MoveLeft();
					
					if ( isTank(enemyObj[i]) || isWall(enemyObj[i]) )
					{
						enemyObj[i]->MoveRight();
						enemyObj[i]->setOtherDirecton();
					}
					break;
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////
// load map and enemy list
//////////////////////////////////////////////////////////////////////

void
Controller::loadMap(const char* mapname)
{
	ifstream fin(mapname);
	if (!fin)	//open file fail
	{
		cerr << "can't open " << mapname << " !!" << endl;
		exit(-1);
	}
	istream_iterator<int> current_pos(fin), end;	// use STL's iterator 
	while (current_pos != end)
	{
		map.push_back(*current_pos);
		++current_pos;
	}
}

void
Controller::loadStage1()
{
	reset(1);

	loadMap(ST1MAP);
	int row = 0;
	int column = 0;
	for (int j = 0; j < map.size(); ++j)
		if (map[j] == 0)
			continue;
		else if ( map[j] == 9)
		{
			row = j / BOARD_WIDTH;		//看是在第幾列
			column = j % BOARD_WIDTH;	//看是在第幾行
			wallObj.push_back(new Wall( TILE_HEIGHT * row, TILE_WIDTH * column));
		} else
		{
			row = j / BOARD_WIDTH;		//看是在第幾列
			column = j % BOARD_WIDTH;	//看是在第幾行
			enemyObj.push_back(new EnemyTank( TILE_HEIGHT*row, TILE_WIDTH*column, map[j]));
		}
	
	bulletObj.push_back( PT->getBullet() );	// Player's bullet is the first of bulletObj
	for (int i = 0; i < enemyObj.size(); ++i)
		bulletObj.push_back(enemyObj[i]->getBullet());
	
	PlaySound(STARTWAV, 0, SND_ASYNC);	// start sound
}

void
Controller::loadStage2()
{
	reset(2);	// 再load之前清除前一關的資料(必須在最前面)

	loadMap(ST2MAP);
	int row = 0;
	int column = 0;
	for (int j = 0; j < map.size(); ++j)
		if (map[j] == 0)
			continue;
		else if ( map[j] == 9)
		{
			row = j / BOARD_WIDTH;		//看是在第幾列
			column = j % BOARD_WIDTH;	//看是在第幾行
			wallObj.push_back( new Wall( TILE_HEIGHT * row, TILE_WIDTH * column) );
		} else
		{
			row = j / BOARD_WIDTH;		//看是在第幾列
			column = j % BOARD_WIDTH;	//看是在第幾行
			enemyObj.push_back(new EnemyTank( TILE_HEIGHT*row, TILE_WIDTH*column, map[j]) );
		}

	// Player's bullet is the first of bulletObj
	bulletObj.push_back( PT->getBullet() );	
	
	for (int i = 0; i < enemyObj.size(); ++i)
		bulletObj.push_back(enemyObj[i]->getBullet());
}

void
Controller::loadStage3()
{
	reset(3);	// 再load之前清除前一關的資料(必須在最前面)
	
	loadMap(ST3MAP);
	int row = 0;
	int column = 0;
	for (int j = 0; j < map.size(); ++j)
		if (map[j] == 0)
			continue;
		else if ( map[j] == 9)
		{
			row = j / BOARD_WIDTH;		//看是在第幾列
			column = j % BOARD_WIDTH;	//看是在第幾行
			wallObj.push_back( new Wall( TILE_HEIGHT * row, TILE_WIDTH * column) );
		} else
		{
			row = j / BOARD_WIDTH;		//看是在第幾列
			column = j % BOARD_WIDTH;	//看是在第幾行
			enemyObj.push_back(new EnemyTank( TILE_HEIGHT*row, TILE_WIDTH*column, map[j]) );
		}

	// Player's bullet is the first of bulletObj
	bulletObj.push_back( PT->getBullet() );	
	
	for (int i = 0; i < enemyObj.size(); ++i)
		bulletObj.push_back(enemyObj[i]->getBullet());
}

void
Controller::clear()
{
	// clear old object
	for (int i = 0; i < bulletObj.size(); ++i)	// 因為每個bullet object都是由tank所控制
		bulletObj[i] = 0;						// 所以不在這做bullet清除的工作
	bulletObj.clear();							// 全部設為0後再clear

	enemyObj.clear();
	wallObj.clear();
	map.clear();
}

void
Controller::reset(int stage)
{
	enemy_dead_count = 0;
	over_clear_key = 90;
	gameover_sound_count = 1;
	stage_title_count = 60;
	stage_flag = stage;
	PT->setDefaultPosition();
	clear();	// 清除vector中的物件
}
void
Controller::showGameMessage()
{
	// 秀出game的訊息(第一關)
	if (stage_flag == 1 && stage_title_count != 0)
	{
		st1Bitmap->drawPixelsA(TILE_WIDTH*BOARD_WIDTH/2-TILE_WIDTH*4,
							TILE_HEIGHT*BOARD_HEIGHT/2-TILE_HEIGHT);
		--stage_title_count;
	}
	// 秀出game的訊息(第二關)
	if (stage_flag == 2 && stage_title_count != 0)
	{
		st2Bitmap->drawPixelsA(TILE_WIDTH*BOARD_WIDTH/2-TILE_WIDTH*4,
							TILE_HEIGHT*BOARD_HEIGHT/2-TILE_HEIGHT);
		--stage_title_count;
	}
	// 秀出game的訊息(第三關)
	if (stage_flag == 3 && stage_title_count != 0)
	{
		st3Bitmap->drawPixelsA(TILE_WIDTH*BOARD_WIDTH/2-TILE_WIDTH*4,
							TILE_HEIGHT*BOARD_HEIGHT/2-TILE_HEIGHT);
		--stage_title_count;
	}

	if (PT->getLife() == 0)	// 如果player死完就印出game over
	{
			goBitmap->drawPixelsA(TILE_WIDTH*BOARD_WIDTH/2-TILE_WIDTH*4,
								TILE_HEIGHT*BOARD_HEIGHT/2-TILE_HEIGHT);
			if (gameover_sound_count == 1)	// gameover只playsound一次
			{
				PlaySound(GAMEOVERWAV, 0, SND_ASYNC);
				--gameover_sound_count;
			}
	}
	
	if ( enemy_dead_count == enemyObj.size() )	// 如過敵人全滅就印出stage clear
	{
		scBitmap->drawPixelsA(TILE_WIDTH*BOARD_WIDTH/2-TILE_WIDTH*6,
							TILE_HEIGHT*BOARD_HEIGHT/2-TILE_HEIGHT);
		if (over_clear_key == 90)
		{
			if (stage_flag != 3)	// play clear sound
				PlaySound(CLEARWAV, 0, SND_ASYNC);
			else
				PlaySound(ALLCLEARWAV, 0, SND_ASYNC);
			--over_clear_key;
		} else if (over_clear_key != 0)
			--over_clear_key;
		else if (stage_flag == 1)
			loadStage2();
		else if (stage_flag == 2)
			loadStage3();
		else
			loadStage1();	// all clear and restart
	}
}

inline
void
Controller::showFloor()
{
	floorBitmap->drawPixels(0, 0);	// 貼一張大背景
}

inline
void
Controller::showWall()
{
	for_each( wallObj.begin(), wallObj.end(), Display() );	// use STL
}

inline
void
Controller::showTank()
{
	for_each( enemyObj.begin(), enemyObj.end(), Display() );	// use STL
	PT->display();
}
//////////////////////////////////////////////////////////////////////
// detect all object collision
//////////////////////////////////////////////////////////////////////

bool
Controller::isTank(Sprite* sp)
{
	bool flag = false;
	flag = sp->collide(PT);	//先看看有沒有跟Player相撞

	for (int i = 0; !flag && i < enemyObj.size(); ++i)	
		if (sp == enemyObj[i])
			continue;	// do nothing
		else
			flag = sp->collide(enemyObj[i]);

	return flag;
}

bool
Controller::isWall(Sprite* sp)
{
	bool flag = false;

	for (int i = 0; !flag && i < wallObj.size(); ++i)
		flag = sp->collide(wallObj[i]);

	return flag;
}

bool
Controller::isBullet(Sprite* sp)
{
	bool flag = false;

	for (int i = 0; !flag && i < bulletObj.size(); ++i)
	{
		flag = bulletObj[i]->collide(sp);
		if(flag)
			bulletObj[i]->setNotVisible();	// set bullet not visible
	}
	
	return flag;
}

bool
Controller::isTank_PT()
{
	bool flag = false;

	for (int i = 0; !flag && i < enemyObj.size(); ++i)	
			flag = PT->collide(enemyObj[i]);

	return flag;
}

void
Controller::checkPlayerBullet()
{
	bool flag = false;

	if ( bulletObj[0]->isVisible() )	// 看看player的bullet是否要顯示在螢幕上
	{
		bulletObj[0]->goAhead();
		for (int i = 0; !flag && i < enemyObj.size(); ++i)	// 看看有沒有撞到tank
		{
			flag = bulletObj[0]->collide(enemyObj[i]);
			if ( flag && !enemyObj[i]->getIfdead() )
			{
				enemyObj[i]->setDead();
				++enemy_dead_count;	// 計算現在死了幾個enemy
				bulletObj[0]->setNotVisible();
			}
		}
		
		if ( bulletObj[0]->isVisible() )	// 檢查有無撞到子彈(子彈相抵銷)
			for (int i = 1; !flag && i < bulletObj.size(); ++i)
			{
				flag = bulletObj[0]->collide(bulletObj[i]);
				if(flag)
				{
					bulletObj[i]->setNotVisible();	// set both bullet not visible
					bulletObj[0]->setNotVisible();
					PlaySound(BULLETCOLLIDE, 0, SND_ASYNC);
				}
			}

		if ( !flag && isWall(bulletObj[0]) )	// 檢查有無撞到牆壁
			bulletObj[0]->setNotVisible();
	}
}

void
Controller::checkEnemyBullet()
{
	bool flag = false;
	for (int i = 1; !flag && i < bulletObj.size(); ++i)
	{
		if ( bulletObj[i]->isVisible() )
			flag = bulletObj[i]->collide(PT);
		if (flag)
		{
			bulletObj[i]->setNotVisible();
			PT->setDead();
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Move enemy's bullets
//////////////////////////////////////////////////////////////////////

void
Controller::bulletMove()
{
	for (int i = 1; i < bulletObj.size(); ++i)
	{
		if ( bulletObj[i]->isVisible() )
		{
			bulletObj[i]->goAhead();
			if ( isWall(bulletObj[i]) )
				bulletObj[i]->setNotVisible();
		}
	}
}

void
Controller::addKeyBuffer(char key)
{
	if (KeyBuffer.size() < 10)
		KeyBuffer.push(key);
}
