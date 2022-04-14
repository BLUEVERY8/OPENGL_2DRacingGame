//날 짜 : 2022.04.07
//작성자 : 강대한
//주 제 : Menu Callback

#include <stdio.h>
#include <glut.h> 
#include <glu.h>
#include <gl.h> 

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.8f, 0.5f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, -0.45, 0.0);
	glVertex3f(0.55, -0.75, 0.0);
	glVertex3f(0.4, -0.25, 0.0);
	glVertex3f(0.75, 0.0, 0.0);
	glVertex3f(0.25, 0.2, 0.0);
	glVertex3f(0.0, 0.65, 0.0);
	glVertex3f(-0.25, 0.2, 0.0);
	glVertex3f(-0.75, 0.0, 0.0);
	glVertex3f(-0.4, -0.25, 0.0);
	glVertex3f(-0.55, -0.75, 0.0);
	glEnd();
	glFlush();
}
void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, (GLsizei)NewWidth, (GLsizei)NewHeight);

	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	gluPerspective(30, (GLdouble)NewWidth / (GLdouble)NewHeight, 1.0, 50.0);
	

	glMatrixMode(GL_MODELVIEW); glLoadIdentity();

	gluLookAt(-5.0, -5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glutPostRedisplay();
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {}

void MySpecial(int key, int X, int Y) {}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {}

void MyMouseMove(GLint X, GLint Y) {}

void MyIdle() {
}

void MyTimer(int Value) {}

void MenuProc(int entryID) {}
void MenuFunc() {}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("제목");
	glClearColor(0.5, 0.5, 0.5, 1.0);

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	MenuFunc();
	glutMainLoop();
	return 0;
}