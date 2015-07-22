#include <GL/glut.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include "data_declaration.h"
#include "controller.h"

static milisecs = 33;		//大概每秒30次計算一次電腦動作(33 for 30 fps)

Controller controller;		//Game Control

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);	
	
	controller.display();

	glFlush();
	glutSwapBuffers();
}

void Keyboard(unsigned char key,int x,int y)
{
	controller.addKeyBuffer(key);
}

void spKeyboard(int key,int x,int y)	// 使用方向鍵
{
	controller.addKeyBuffer(key);
}

void nextFrame(int value)
{
	controller.enemyAI();
	glutPostRedisplay();
	glutTimerFunc(milisecs, nextFrame,0);
}

void init()
{
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(BOARD_WIDTH*TILE_WIDTH, BOARD_HEIGHT*TILE_HEIGHT);
    glutCreateWindow("Tank Battle"); /* window title */
    
	// set function
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(spKeyboard);
	glutTimerFunc(milisecs, nextFrame,0);

    glClearColor(0.0, 0.0, 0.0, 0.0); /* black background */

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLfloat) BOARD_WIDTH*TILE_WIDTH, 0.0, (GLfloat) BOARD_HEIGHT*TILE_HEIGHT);
    glMatrixMode(GL_MODELVIEW);

	srand( (unsigned) time(NULL) );
}

int main()
{
	init();
	glutMainLoop();
	return 0;
}
