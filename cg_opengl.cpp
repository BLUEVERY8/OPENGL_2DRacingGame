//날 짜 : 2022.03.31
//작성자 : 강대한
//주 제 : Timer 활용

#include <stdio.h>
#include <glut.h>
#include <glu.h>
#include <gl.h>

GLfloat Delta = 0.0;
GLfloat seta = 0.0, R=0, G=0, B=0;
GLint flag1 = 0;
GLint flag2 = 0, val=1;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(R, G, B);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5 + Delta, -0.25 + seta, 0.0);
	glVertex3f(0.0 + Delta, -0.25 + seta, 0.0);
	glVertex3f(0.0 + Delta, 0.25 + seta, 0.0);
	glVertex3f(-0.5 + Delta, 0.25 + seta, 0.0);
	glEnd();
	glFlush();

}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {}

void MyIdle() {
	if (flag1 == 0)
		Delta = Delta + 0.0035;
	else
		Delta = Delta - 0.0035;
	if (Delta > 1) {
		flag1 = 1;
	}

	else if (Delta < -0.5) {
		flag1 = 0;
	}

	if (flag2 == 0)
		seta = seta + 0.001;
	else
		seta = seta - 0.001;
	if (seta > 0.75) {
		flag2 = 1;
	}

	else if (seta < -0.75) {
		flag2 = 0;
	}
	glutPostRedisplay();
}

void MyTimer(int Value) {
	if (Value == 1) {
		R = 0.3, G = 0.5, B = 0.8;
		if (flag1 == 0)
			Delta = Delta + 0.2;
		else
			Delta = Delta - 0.2;
		if (Delta > 1) {
			flag1 = 1;
			val = 2;
		}

		else if (Delta < -0.5) {
			flag1 = 0;
			val = 2;
		}

		/*if (flag2 == 0)
			seta = seta + 0.2;
		else
			seta = seta - 0.2;
		if (seta > 0.75) {
			flag2 = 1;
		}

		else if (seta < -0.75) {
			flag2 = 0;
		}*/
		glutPostRedisplay();
		glutTimerFunc(200, MyTimer, val);
	}
	else if (Value == 2) {
		R = 0.7, G = 0.4, B = 0.2;
		/*if (flag1 == 0)
			Delta = Delta + 0.2;
		else
			Delta = Delta - 0.2;
		if (Delta > 1) {
			flag1 = 1;
		}

		else if (Delta < -0.5) {
			flag1 = 0;
		}*/

		if (flag2 == 0)
			seta = seta + 0.2;
		else
			seta = seta - 0.2;
		if (seta > 0.75) {
			flag2 = 1;
			val = 1;
		}

		else if (seta < -0.75) {
			flag2 = 0;
			val = 1;
		}
		glutPostRedisplay();
		glutTimerFunc(200, MyTimer, val);
	}
}
void MyReshape(int NewWidth, int NewHeight) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
}

void initUse() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	printf("학과 학번 이름 \n 날짜: ~~ \n 주제: ~~");

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("제목");
	initUse();

	glutDisplayFunc(MyDisplay);
	//glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	//glutIdleFunc(MyIdle);
	glutTimerFunc(200, MyTimer, val);

	glutTimerFunc(200, MyTimer, val);
	glutMainLoop();
	return 0;
}