//날 짜 : 2022.04.07
//작성자 : 강대한
//주 제 : Menu Callback

#include <stdio.h>
#include <glut.h> 
#include <glu.h>
#include <gl.h> 
int menuValue, sizeMenu, ColorMenu, shapeMenu;
double sizeValue = 0.5f;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (ColorMenu == 11) glColor3f(1.0f, 0.0f, 0.0f);
	else if (ColorMenu == 12) glColor3f(0.0f, 1.0f, 0.0f);
	else if (ColorMenu == 13) glColor3f(0.0f, 0.0f, 1.0f);
	else glColor3f(1.0f, 1.0f, 0.0f);

	if (sizeMenu == 21) { sizeValue += 0.1; sizeMenu = 0; }
	else if (sizeMenu == 22) { sizeValue -= 0.1; sizeMenu = 0; }

	if (shapeMenu == 1) glutSolidSphere(sizeValue, 8, 5);
	else if (shapeMenu == 2) glutSolidTorus(0.1, sizeValue, 50, 10);
	else { glBegin(GL_POLYGON);
					glVertex3f(-sizeValue, -sizeValue, 0.0);
					glVertex3f(sizeValue, -sizeValue, 0.0);
					glVertex3f(sizeValue, sizeValue, 0.0);
					glVertex3f(-sizeValue, sizeValue, 0.0);
					glEnd();
	}
	glFlush();
}
void MyReshape(int NewWidth, int NewHeight) { }

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {}

void MySpecial(int key, int X, int Y) {}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {}

void MyMouseMove(GLint X, GLint Y) {}

void MyIdle() {
}

void MyTimer(int Value) {}

void MenuProc(int entryID) {
	printf("선택한 메뉴=>%d\n", entryID);
	if (entryID == 3) exit(0);
	else if (entryID >= 20) sizeMenu = entryID;
	else if (entryID >= 10) ColorMenu = entryID;
	else shapeMenu = entryID;
	glutPostRedisplay();
}void MenuFunc() {
	GLint MySubMenuSize = glutCreateMenu(MenuProc);
	glutAddMenuEntry("big", 21); glutAddMenuEntry("small", 22);

	GLint MySubMenuID = glutCreateMenu(MenuProc);
	glutAddMenuEntry("red", 11); glutAddMenuEntry("green", 12);
	glutAddMenuEntry("blue", 13);

	GLint MyMainMenuID = glutCreateMenu(MenuProc);
	glutAddMenuEntry("Draw Sphere", 1);
	glutAddMenuEntry("Draw Torue", 2);
	glutAddSubMenu("Color", MySubMenuID);
	glutAddSubMenu("Size", MySubMenuSize);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAddMenuEntry("?", 4);

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("제목");
	glClearColor(0.5, 0.5, 0.5, 1.0);

	glutDisplayFunc(MyDisplay);
	MenuFunc();
	glutMainLoop();
	return 0;
}