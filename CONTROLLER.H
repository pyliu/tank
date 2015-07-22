// controller.h: interface for the Controller class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLLER_H__85879DD5_1DF2_4343_ABE6_71B01DBBC494__INCLUDED_)
#define AFX_CONTROLLER_H__85879DD5_1DF2_4343_ABE6_71B01DBBC494__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//////////////////////////////////////////////////////////////////////

#include <vector>
#include <queue>
class Sprite;
class PlayerTank;
class EnemyTank;
class Wall;
class Bullet;
class DIBitmap;
using namespace std;

// 控制全部物件的class
class Controller  
{
private: // data
	vector<Wall *> wallObj;
	vector<EnemyTank *> enemyObj;
	vector<Bullet *> bulletObj;
	vector<int> map;
	queue<char> KeyBuffer;	// keyboard buffer(for smooth moving)
	
	PlayerTank* PT;
	int enemy_dead_count;
	int stage_title_count;		// default is 60 (2 sec)
	int stage_flag;				// default is 1
	int over_clear_key;			// default is 90 (3 sec)
	int gameover_sound_count;	// default is 1
	
	DIBitmap* goBitmap;		// gameover的bitmap
	DIBitmap* scBitmap;		// StageClear的bitmap
	DIBitmap* st1Bitmap;	// Stage1start的bitmap
	DIBitmap* st2Bitmap;	// Stage2start的bitmap
	DIBitmap* st3Bitmap;	// Stage3start的bitmap
	DIBitmap* floorBitmap;	// 地板的bitmap

public: // open interface

	Controller();
	void addKeyBuffer(char key);
	void enemyAI();
	void display();
	~Controller();

private:

	void loadMap(const char* mapname);
	void loadStage1();
	void loadStage2();
	void loadStage3();
	void showGameMessage();
	void showFloor();
	void showWall();
	void showTank();
	void reset(int stage);
	void clear();

	void bulletMove();
	void playerMove();
	void enemyMove();

	bool isTank(Sprite* sp);	// sp是要提出偵測的物件
	bool isWall(Sprite* sp);
	bool isBullet(Sprite* sp);
	bool isTank_PT();			//給playertank用來偵測tank是否相撞
	void checkPlayerBullet();	// 檢查player的bullet是否打到enemy
	void checkEnemyBullet();	// 檢查enemy的bullet是否打到player
};

//////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_CONTROLLER_H__85879DD5_1DF2_4343_ABE6_71B01DBBC494__INCLUDED_)
