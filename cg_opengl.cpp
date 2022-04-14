////날 짜 : 2022.04.07
////작성자 : 강대한
////주 제 : Menu Callback
//
//#include <stdio.h>
//#include <glut.h> 
//#include <glu.h>
//#include <gl.h> 
//
//void MyDisplay() {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(0.8f, 0.5f, 1.0f);
//	glBegin(GL_POLYGON);
//	glVertex3f(0.0, -0.45, 0.0);
//	glVertex3f(0.55, -0.75, 0.0);
//	glVertex3f(0.4, -0.25, 0.0);
//	glVertex3f(0.75, 0.0, 0.0);
//	glVertex3f(0.25, 0.2, 0.0);
//	glVertex3f(0.0, 0.65, 0.0);
//	glVertex3f(-0.25, 0.2, 0.0);
//	glVertex3f(-0.75, 0.0, 0.0);
//	glVertex3f(-0.4, -0.25, 0.0);
//	glVertex3f(-0.55, -0.75, 0.0);
//	glEnd();
//	glFlush();
//}
//void MyReshape(int NewWidth, int NewHeight) {
//	glViewport(0, 0, NewWidth, NewHeight);
//	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)500; // 확대, 축소 비율 지정
//	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)500;
//
//	glMatrixMode(GL_PROJECTION); glLoadIdentity();
//	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
//
//	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
//}
//
//void MyKeyboard(unsigned char KeyPressed, int X, int Y) {}
//
//void MySpecial(int key, int X, int Y) {}
//
//void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {}
//
//void MyMouseMove(GLint X, GLint Y) {}
//
//void MyIdle() {
//}
//
//void MyTimer(int Value) {}
//
//void MenuProc(int entryID) {}
//void MenuFunc() {}
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB);
//	glutInitWindowSize(500, 500);
//	glutInitWindowPosition(100, 200);
//	glutCreateWindow("제목");
//	glClearColor(0.5, 0.5, 0.5, 1.0);
//
//	glutDisplayFunc(MyDisplay);
//	glutReshapeFunc(MyReshape);
//	MenuFunc();
//	glutMainLoop();
//	return 0;
//}

#include <glut.h>

#include <glu.h>

#include <gl.h>

#include <stdio.h>

#include <stdlib.h>

#include <time.h>

float R = 0.0, G = 0.0, B = 1.0;

GLfloat  x = 0, y = 0;

int XGPS = 0, YGPS = 0;





void MyDisplay() {

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(R, G, B);



	glBegin(GL_POLYGON);

	glVertex3f(x, y, 0.0);

	glVertex3f(x + 320, y, 0.0);

	glVertex3f(x + 320, y + 320, 0.0);

	glVertex3f(x, y + 320, 0.0);



	glEnd();

	glFlush();

}



void MyReshape(int NewWidth, int NewHeight) {

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glOrtho(0, 1920, 1080, 0, -5.0, 5.0);

}





void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {

	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {

		x = X;

		y = Y;

		XGPS = rand() % 2;

		YGPS = rand() % 2;



		R = (float)(rand() % 10) / 10;

		G = (float)(rand() % 10) / 10;

		B = (float)(rand() % 10) / 10;

		printf("CLICK -> %f %f %f\n", R, G, B);

		printf("CLICK -> %d %d\n", X, Y);

	}

}



void MyTimer(int Value) {

	if (x > 1600) {

		XGPS = 1;

	}

	else if (x < 0) {

		XGPS = 0;

	}

	if (XGPS == 0)

		x += 10;

	else if (XGPS == 1)

		x -= 10;

	if (y > 720) {

		YGPS = 1;

	}

	else if (y < 0) {

		YGPS = 0;

	}

	if (YGPS == 0)

		y += 10;

	else if (YGPS == 1)

		y -= 10;

	glutTimerFunc(10, MyTimer, 1);

	glutPostRedisplay();

}



int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(1920, 1080);

	glutInitWindowPosition(0, 0);

	glutCreateWindow("메모장");

	glClearColor(1.0, 1.0, 1.0, 1.0);

	srand((unsigned)time(NULL));



	glutDisplayFunc(MyDisplay);

	glutReshapeFunc(MyReshape);



	glutMouseFunc(MyMouseClick);

	//glutIdleFunc(MyIdle);

	glutTimerFunc(10, MyTimer, 1);



	glutMainLoop();

	return 0;

}