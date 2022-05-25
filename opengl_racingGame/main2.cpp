#pragma warning (disable:4996)
#include <windows.h>
#include <glut.h>
#include <glu.h>
#include <gl.h>

#include <stdlib.h>
#include <stdio.h>



int isGaming = 0, FPS = 50, score = 0;

int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;

int xCar = 0;
int yCar = 0;

//Car Coming
int car1 = 0;
int lrIndex1 = 0;
int car2 = +35;
int lrIndex2 = 0;
int car3 = +70;
int lrIndex3 = 0;

GLint R = 1, G = 1, B = 1;

const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;

char buffer1[50], buffer2[50];

int record[50], n;
char player;

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
	roadDivTop--;
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



	roadDivMdl--;
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
	roadDivBtm--;
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
	glVertex2f(xCar + 26 - 2, yCar + 5);
	glVertex2f(xCar + 26 - 2, yCar + 7);
	glVertex2f(xCar + 30 + 2, yCar + 7);
	glVertex2f(xCar + 30 + 2, yCar + 5);
	glEnd();
	//Back Tire
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(xCar + 26 - 2, yCar + 1);
	glVertex2f(xCar + 26 - 2, yCar + 3);
	glVertex2f(xCar + 30 + 2, yCar + 3);
	glVertex2f(xCar + 30 + 2, yCar + 1);
	glEnd();
	//Car Body
	glColor3f(R, G, B);
	glBegin(GL_POLYGON);
	glVertex2f(xCar + 26 - 0.47, yCar + 1);
	glVertex2f(xCar + 26 - 0.47, yCar + 6.5);
	glVertex2f(xCar + 26 - 0.22, yCar + 8);
	glVertex2f(xCar + 30 + 0.25, yCar + 8);
	glVertex2f(xCar + 30 + 0.5, yCar + 6.5);
	glVertex2f(xCar + 30 + 0.5, yCar + 1);
	glEnd();

}
void Record() {
	printf("Insert Player Name : ");
	scanf("%c", &player);
	printf("%c's score : %d\n", player, record[n]);
	n++;
}
//이름입력 -> player's 점수 : n점
void startMenu()
{
	if (isGaming == 0)
	{
		glColor3f(1.000, 1.000, 0.000);
		renderBitmapString(30, 80, (void*)font1, "The racer");

		glColor3f(0.000, 1.000, 0.000);
		renderBitmapString(30, 50 + 10, (void*)font2, "Press SPACE to START");

		glColor3f(1.000, 1.000, 1.000);
		renderBitmapString(30, 50 - 10 + 10, (void*)font3, "Press LEFT to turn Left");
		renderBitmapString(30, 50 - 12 + 10, (void*)font3, "Press RIGHT to turn Right");
		renderBitmapString(30, 50 - 14 + 10, (void*)font3, "Press UP to turn Up");
		renderBitmapString(30, 50 - 16 + 10, (void*)font3, "Press DOWN to turn Down");
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
		Record();
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
void myTimer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, myTimer, 0);
}

void mySpecialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT)
	{
		if (xCar <= 44) {
			xCar = xCar + (FPS / 15);
			if (xCar > 44) {
				xCar = 45;
			}
		}
	}
	else if (key == GLUT_KEY_LEFT)
	{
		if (xCar >= 0) {
			xCar = xCar - (FPS / 15);
			if (xCar < 0) {
				xCar = -1;
			}
		}
	}
	if (key == GLUT_KEY_UP)
	{
		if (yCar <= 9) {
			yCar = yCar + (FPS / 20);
			if (yCar > 9) {
				yCar = 8;
			}
		}
	}
	else if (key == GLUT_KEY_DOWN)
	{
		if (yCar >= 0) {
			yCar = yCar - (FPS / 20);
			if (yCar < 0) {
				yCar = 0;
			}
		}
	}
}
void myKey(unsigned char key, int x, int y)
{
	if (isGaming == 0 || isGaming == 2)
	{
		if (key == 32)
			isGaming = 1;
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

	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialKey);
	glutKeyboardFunc(myKey);
	glutTimerFunc(1000, myTimer, 0);
	

	glutMainLoop();

	return 0;
}