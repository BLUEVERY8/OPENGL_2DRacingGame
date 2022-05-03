#include <glut.h>
#include <glu.h>
#include <gl.h>


void MyDis() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireTeapot(0.5);
	glBegin(GL_LINES);
		glVertex3f(0, -5.0, 0.0); glVertex3f(0, 5.0, 0.0);
		glVertex3f(-5.0, 0.0, 0.0); glVertex3f(5.0, 0.0, 0.0);
	glEnd();

	glRotatef(180.0f, 1.0f, 1.0f, 0.0);
	glTranslatef(3.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireTeapot(0.5);
	glBegin(GL_LINES);
	glVertex3f(0, -5.0, 0.0); glVertex3f(0, 5.0, 0.0);
	glVertex3f(-5.0, 0.0, 0.0); glVertex3f(5.0, 0.0, 0.0);
	glEnd();

	
	glFlush();
}
void MyRes(int NW, int NH) {
	GLfloat nRange = 5.0f;
	if (NH == 0)
		NH = 1;
	glViewport(0, 0, NW, NH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (NW <= NH)
		glOrtho(-nRange, nRange, -nRange * NH / NW, nRange * NH / NW, -nRange, nRange);
	else
		glOrtho(-nRange * NW / NH, nRange * NW / NH, -nRange, nRange, -nRange, nRange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
