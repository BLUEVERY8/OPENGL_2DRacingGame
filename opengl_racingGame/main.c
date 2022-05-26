#pragma warning (disable:4996)
#include <windows.h>
#include <glut.h>
#include <glu.h>
#include <gl.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int isGaming = 0, FPS = 50, score = 0, speed = 1, i=0, boosterFlag = 0, isBoosting=0,randomBooster;

int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;

int lrIndex = 0;

//Car Coming
int coin1 = 0;
int coinIdx1 = 0;
int booster = 0;
int boosterIdx = 0;


const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;

char buffer1[50], buffer2[50];
void renderBitmapString(float x, float y, void* font, const char* string)
{
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

void startGame()
{
	glColor3f(0.412, 0.412, 0.412);
	glBegin(GL_POLYGON);
	glVertex2f(20, 0);
	glVertex2f(20, 100);
	glVertex2f(80, 100);
	glVertex2f(80, 0);
	glEnd();

	//Road Left Border
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(20, 0);
	glVertex2f(20, 100);
	glVertex2f(23, 100);
	glVertex2f(23, 0);
	glEnd();

	//Road Right Border
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(77, 0);
	glVertex2f(77, 100);
	glVertex2f(80, 100);
	glVertex2f(80, 0);
	glEnd();

	//Road Middel Border
	  //TOP
	glColor3f(1.000, 1.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivTop + 80);
	glVertex2f(48, roadDivTop + 100);
	glVertex2f(52, roadDivTop + 100);
	glVertex2f(52, roadDivTop + 80);
	glEnd();
	roadDivTop -= speed;
	if (roadDivTop < -100) {
		roadDivTop = 20;
		score++;
	}
	glColor3f(1.000, 1.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivMdl + 40);
	glVertex2f(48, roadDivMdl + 60);
	glVertex2f(52, roadDivMdl + 60);
	glVertex2f(52, roadDivMdl + 40);
	glEnd();



	roadDivMdl -= speed;
	if (roadDivMdl < -60) {
		roadDivMdl = 60;
		score++;
	}
	//Bottom
	glColor3f(1.000, 1.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivBtm + 0);
	glVertex2f(48, roadDivBtm + 20);
	glVertex2f(52, roadDivBtm + 20);
	glVertex2f(52, roadDivBtm + 0);
	glEnd();
	roadDivBtm -= speed;
	if (roadDivBtm < -20) {
		roadDivBtm = 100;
		score++;
	}
	//Score Board
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(80, 97);
	glVertex2f(100, 97);
	glVertex2f(100, 98 - 8);
	glVertex2f(80, 98 - 8);
	glEnd();


	sprintf(buffer1, "SCORE: %d", score);
	glColor3f(0.000, 1.000, 0.000);
	renderBitmapString(80.5, 95, (void*)font3, buffer1);

	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26 - 2, 5);
	glVertex2f(lrIndex + 26 - 2, 7);
	glVertex2f(lrIndex + 30 + 2, 7);
	glVertex2f(lrIndex + 30 + 2, 5);
	glEnd();
	//Back Tire
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26 - 2, 1);
	glVertex2f(lrIndex + 26 - 2, 3);
	glVertex2f(lrIndex + 30 + 2, 3);
	glVertex2f(lrIndex + 30 + 2, 1);
	glEnd();
	//Car Body
	glColor3f(0.678, 1.000, 0.184);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26, 1);
	glVertex2f(lrIndex + 26, 8);
	glColor3f(0.000, 0.545, 0.545);

	glVertex2f(lrIndex + 28, 10);
	glVertex2f(lrIndex + 30, 8);
	glVertex2f(lrIndex + 30, 1);
	glEnd();

	//코인(점수증가)
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(coinIdx1 + 26 - 2, coin1 + 100 - 4);
	glVertex2f(coinIdx1 + 26 - 2, coin1 + 100 - 6);
	glVertex2f(coinIdx1 + 30 + 2, coin1 + 100 - 6);
	glVertex2f(coinIdx1 + 30 + 2, coin1 + 100 - 4);
	glEnd();
	coin1 -= speed;
	if ((abs(lrIndex - coinIdx1) < 8) && (coin1 + 100 < 10)) {
		score += 3;
		coinIdx1 = rand() % 45;
		coin1 = 0;
	}
	else if (coin1 < -100)
	{
		coinIdx1 = rand() % 45;
		coin1 = 0;
	}
	
	//부스터(속도 증가)
	if (isBoosting == 0)
	{
		randomBooster = rand() % 20;
	}
	if (randomBooster == 8)
	{
		isBoosting = 1;
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(boosterIdx + 26 - 2, booster + 100 - 4);
		glVertex2f(boosterIdx + 26 - 2, booster + 100 - 6);
		glVertex2f(boosterIdx + 30 + 2, booster + 100 - 6);
		glVertex2f(boosterIdx + 30 + 2, booster + 100 - 4);
		glEnd();
		if (speed == 1)
			booster--;
		else
			booster -= speed;
		if ((abs(lrIndex - boosterIdx) < 8) && (booster + 100 < 10)) {
			speed = 3;
			boosterIdx = rand() % 45;
			booster = 0;
			isBoosting = 0;
			boosterFlag = 1;
		}
		else if (booster < -100)
		{
			boosterIdx = rand() % 45;
			booster = 0;
			isBoosting = 0;
		}
	}
	
	
}
void startMenu()
{
	if (isGaming == 0)
	{
		glColor3f(1.000, 1.000, 0.000);
		renderBitmapString(30, 80, (void*)font1, "The racer");

		glColor3f(0.000, 1.000, 0.000);
		renderBitmapString(30, 50 + 10, (void*)font2, "Press SPACE to START");

		glColor3f(1.000, 1.000, 1.000);
		renderBitmapString(30, 50 - 10 + 10, (void*)font3, "Press RIGHT to turn Right");
		renderBitmapString(30, 50 - 12 + 10, (void*)font3, "Press LEFT to turn Left");
	}
	else
	{
		glColor3f(1.0, 0.0, 0.0);
		renderBitmapString(35, 50, (void*)font1, "GAME OVER");
		glColor3f(1.0, 0.0, 0.0);
		sprintf(buffer2, "Score : %d", score);
		renderBitmapString(33, 66, (void*)font1, buffer2);
		glColor3f(1.0, 0.0, 0.0);
		renderBitmapString(30, 40, (void*)font1, "If you want to restart game Press space bar");
	}
}
void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (isGaming == 1)
	{
		glClearColor(0.0, 0.4, 0.0, 1);
		startGame();
	}
	else
		startMenu();
	glFlush();
	glutSwapBuffers();
}
void myTimer(int value)
{
	if (value == 0)
	{
		i++;
		if (i == 500)
			speed = 1;
		if (boosterFlag == 1)
		{
			boosterFlag = 0;
			glutPostRedisplay();
			glutTimerFunc(1000 / FPS, myTimer, 1);
		}
		else
		{
			glutPostRedisplay();
			glutTimerFunc(1000 / FPS, myTimer, 0);
		}		
	}
	else if (value == 1)
	{
		i = 0;
		glutPostRedisplay();
		glutTimerFunc(1000 / FPS, myTimer, 0);
		
	}
	
}

void mySpecialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT)
	{
		if (lrIndex <= 44) {
			lrIndex = lrIndex + (FPS / 10);
			if (lrIndex > 44) {
				lrIndex = 45;
			}
		}
	}
	else if (key == GLUT_KEY_LEFT)
	{
		if (lrIndex >= 0) {
			lrIndex = lrIndex - (FPS / 10);
			if (lrIndex < 0) {
				lrIndex = -1;
			}
		}
	}
}
void myKey(unsigned char key, int x, int y)
{
	if (isGaming == 0 || isGaming == 2)
	{
		if (key == 32) 
		{
			coinIdx1 = rand() % 45;
			isGaming = 1;
		}
			
	}
	glutPostRedisplay();
}
void init()
{
	glOrtho(0, 100, 0, 100, -1, 1);
	glClearColor(0.184, 0.310, 0.310, 1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 650);
	glutInitWindowPosition(200, 20);
	glutCreateWindow("The racer");
	init();
	srand((unsigned int)time(NULL));
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialKey);
	glutKeyboardFunc(myKey);
	glutTimerFunc(1000, myTimer, 0);


	glutMainLoop();

	return 0;
}