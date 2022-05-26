#include <glut.h>
#include <glu.h>
#include <gl.h>
static int SpinAngle = 0;

void myDisplay() {
	GLfloat LightPosition[] = { 0.0, 0.0, 1.5, 1.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);
	glPushMatrix();
	glRotatef(SpinAngle, 1.0, 0.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glTranslatef(0.0, 0.0, 1.5);
	glDisable(GL_LIGHTING);
	glColor3f(0.9, 0.9, 0.9);
	glutWireSphere(0.06, 10, 10);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glutSolidSphere(1.0, 400, 400);
	glPopMatrix();
	glFlush();
}
void myReshape(int w, int h) {
	
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void MyKey(unsigned char key, int x, int y) {

}
void MySpe(int key, int x, int y) {

}
void myMouse(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		SpinAngle = (SpinAngle + 15) % 360;
		glutPostRedisplay;
	}
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
void initLight()
{
	GLfloat light0_ambient[] = {0.5, 0.4, 0.3, 1.0};
	GLfloat light0_diffuse[] = {0.8, 0.7, 0.6, 1.0};
	GLfloat light0_specular[] = {1.0, 1.0, 1.0, 1.0};

	GLfloat material_ambient[] = {0.4, 0.4, 0.4, 1.0};
	GLfloat material_diffuse[] = {0.9, 0.9, 0.9, 1.0};
	GLfloat material_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat material_shininess[] = {25.0};

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("제목");
	initLight();

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	/*glutKeyboardFunc(MyKey);
	glutSpecialFunc(MySpe);*/
	glutMouseFunc(myMouse);
	/*glutMotionFunc(MyMove);
	glutIdleFunc(MyIdle);
	glutTimerFunc(40,MyTim,1);*/
	

	glutMainLoop();
	return 0;

}
