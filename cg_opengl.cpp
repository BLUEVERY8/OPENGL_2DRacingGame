﻿#include <glut.h>
#include <glu.h>
#include <gl.h>


void MyDis() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	
	/*glScalef(2.0, 2.0, 2.0);
	glTranslatef(0.5, 0.5, 0.0);*/

	glRotatef(90.0f, 1, 0, 0);
	glutWireTeapot(0.25);

	/*glTranslatef(-0.5, 0.5, 0.0);
	glScalef(0.5, 0.5, 0.5);*/
	glFlush();
}
void MyRes(int NW, int NH) {
}
void MyKey(unsigned char key, int x, int y) {

}
void MySpe(int key, int x, int y) {

}
void MyClick(GLint button, GLint state, GLint x, GLint y) {

}
void MyMove(GLint x, GLint y) {

}
void MyIdle() {

}
void MyTim(int value) {

}
void MenuProc(int entryid) {

}
void MenuFunc() {

}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("제목");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutDisplayFunc(MyDis);
	glutReshapeFunc(MyRes);
	glutKeyboardFunc(MyKey);
	glutSpecialFunc(MySpe);
	glutMouseFunc(MyClick);
	glutMotionFunc(MyMove);
	glutIdleFunc(MyIdle);
	glutTimerFunc(40,MyTim,1);
	MenuFunc();

	glutMainLoop();
	return 0;

}
