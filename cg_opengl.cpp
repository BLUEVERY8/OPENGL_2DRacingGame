//날 짜 : 2022.03.31
//작성자 : 강대한
//주 제 : Timer 활용

#include <stdio.h>
#include <conio.h>
#include <glut.h>
#include <glu.h>
#include <gl.h>

GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;
int NewWi, NewHe, temp = 0;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.05, 0.05, 0.0);
	glVertex3f(0.05, 0.95, 0.0);
	glVertex3f(0.95, 0.95, 0.0);
	glVertex3f(0.95, 0.05, 0.0);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(TopLeftX / (float)NewWi, (NewHe - TopLeftY) / (float)NewHe, 0.0);
	glVertex3f(TopLeftX / (float)NewWi, (NewHe - BottomRightY) / (float)NewHe, 0.0);
	glVertex3f(BottomRightX / (float)NewWi, (NewHe - BottomRightY) / (float)NewHe, 0.0);
	glVertex3f(BottomRightX / (float)NewWi, (NewHe - TopLeftY) / (float)NewHe, 0.0);
	glEnd();
	glFlush();

}

void MyReshape(int NW, int NH) {
	glViewport(0, 0, NW, NH);
	NewWi = NW; NewHe = NH;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		TopLeftX = X; TopLeftY = Y;
		printf("click-> %d %d \n", X, Y);
		temp = 1;
	}
	else
		temp = 0;
}

void MyMouseMove(GLint X, GLint Y) {
	if (temp == 1 ) {
		BottomRightX = X; BottomRightY = Y;
		printf("move-> %d %d \n", X, Y);
		glutPostRedisplay();
	}
	
}

void initUse() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	printf("학과 학번 이름 \n 날짜: ~~ \n 주제: ~~");

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowSize(700, 700);
	glutCreateWindow("제목");
	initUse();

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutMainLoop();
	return 0;
}