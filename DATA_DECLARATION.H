#ifndef _DATA_DECLARATION_H
#define _DATA_DECLARATION_H

// effective C++ principle 21
// use const as possible as you can, not use macro

// 設定版面可以有幾個TILES
const int BOARD_WIDTH	= 16;
const int BOARD_HEIGHT	= 16;
// TILES的長寬佔多少個pixels
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

// define direction code
const int NORTH	= 0;
const int EAST	= 1;
const int SOUTH	= 2;
const int WEST	= 3;

// used bitmap file name
const char* const pNORTHBITMAP	= "Bitmap\\ptUP.bmp";
const char* const pEASTBITMAP	= "Bitmap\\ptRight.bmp";
const char* const pSOUTHBITMAP	= "Bitmap\\ptDOWN.bmp";
const char* const pWESTBITMAP	= "Bitmap\\ptLEFT.bmp";

const char* const eNORTHBITMAP	= "Bitmap\\etUP.bmp";
const char* const eEASTBITMAP	= "Bitmap\\etRIGHT.bmp";	
const char* const eSOUTHBITMAP	= "Bitmap\\etDOWN.bmp";
const char* const eWESTBITMAP	= "Bitmap\\etLEFT.bmp";

const char* const WALLBITMAP	= "Bitmap\\wall.bmp";
const char* const FLOORBITMAP	= "Bitmap\\floor.bmp";
const char* const BULLETBITMAP	= "Bitmap\\bullet.bmp";
const char* const GOBITMAP		= "Bitmap\\gameover.bmp";
const char* const DIEBITMAP1	= "Bitmap\\die1.bmp";
const char* const DIEBITMAP2	= "Bitmap\\die2.bmp";
const char* const SCBITMAP		= "Bitmap\\StageClear.bmp";
const char* const STAGE1START	= "Bitmap\\Stage1start.bmp";
const char* const STAGE2START	= "Bitmap\\Stage2start.bmp";
const char* const STAGE3START	= "Bitmap\\Stage3start.bmp";

// uesd wave file name
const char* const SHOOTWAV		= "wav\\shoot.wav";
const char* const DEADWAV		= "wav\\dead.wav";
const char* const ENGINEWAV		= "wav\\engine.wav";
const char* const CLEARWAV		= "wav\\clear.wav";
const char* const REMINDERWAV	= "wav\\reminder.wav";
const char* const STARTWAV		= "wav\\start.wav";
const char* const GAMEOVERWAV	= "wav\\gameover.wav";
const char* const BULLETCOLLIDE = "wav\\bulletcollide.wav";
const char* const ALLCLEARWAV	= "wav\\allclear.wav";

// used txt file name
const char* const ST1MAP		= "txt\\st1map.txt";
const char* const ST2MAP		= "txt\\st2map.txt";
const char* const ST3MAP		= "txt\\st3map.txt";

#endif