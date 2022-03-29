
//날 짜 : 2022.03.29
//작성자 : 강대한
//주 제 : 콜백 관련 함수
#include <stdio.h>
#include <glut.h>														//운영체제 연결
#include <glu.h>														//그림 그리기
#include <gl.h>															//렌더링
#include <math.h>
#define GL_PI 3.1415f
int count = 0, reCount = 0;

void MyDisplay() {
	int iPivot = 1;
	float Size[2];
	GLfloat x, y, z, angle;

	count++;
	printf("%d 디스플레이 호출", count);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);					//버퍼 초기화
	glColor3f(0.0f, 1.0f, 0.0f);
	glutWireOctahedron();
	//glutWireTeapot(0.5);
	//glutWireCone(0.5, 0.7, 10, 20);
	//glutWireTorus(0.5, 0.5, 10, 20);
	//glutWireCube(0.5);
	//glutSolidSphere(0.5, 100, 200);
	//glutWireSphere(0.5, 10, 20);
	
	//glGetFloatv(GL_POINT_SIZE_RANGE, Size);
	//printf("최소 %f \n최대 %f\n", Size[0], Size[1]);
	//glPointSize(Size[1]);												// 점의 크기
	//glBegin(GL_POINTS);												// 점들을 면으로
	//
	//z = -0.8f;
	//for (angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle += 0.1f) {
	//	x = sin(angle)/2;
	//	y = cos(angle)/2;
	//	glVertex3f(x, y, z);
	//	z += 0.02f;
	//}
	//glEnd();
	//glLineWidth(5.0f);
	//glBegin(GL_LINE_STRIP); // //GL_LINES  //GL_LINE_LOOP
	//z = 0.0f;
	//for (angle = 0.0f; angle <= GL_PI*2*4; angle += 0.1f) {
	//	x = sin(angle) / 1.5;
	//	y = cos(angle) / 1.5;
	//	glVertex3f(x, y, z);
	//	z += 0.05f;
	//	x = (sin(angle + GL_PI)) / 1.5;
	//	y = (cos(angle + GL_PI)) / 1.5;
	//	glVertex3f(x, y, z);
	//}
	//glShadeModel(GL_FLAT); //GL_SMOOTH
	//glBegin(GL_TRIANGLE_FAN);
	//glVertex3f(0.0f, 0.0f, 1.0f);
	//for (angle = 0.0f; angle < (4.0f * GL_PI); angle += (GL_PI / 4.0f)) {
	//	x = sin(angle)/1.5f; y = cos(angle)/1.5;
	//	if ((iPivot % 2) == 0)
	//		glColor3f(0.0f, 1.0f, 0.0f);
	//	else
	//		glColor3f(1.0f, 0.0f, 0.0f);
	//	iPivot++;
	//	glVertex2f(x, y);
	//}
	glEnd();
	glutSwapBuffers();
}
void MyReshape(int NewWidth, int NewHeight) { // 균형 유지 위한 변형값을 인자로 받음 (자동) 결과창의 크기 위치 변경시 호출됨
	reCount++;
	printf("%d 리세이프 호출", reCount);
	printf("새창너비 %d 새창높이 %d\n", NewWidth, NewHeight);
}								
void MyKeyboard(unsigned char KeyPressed, int X, int Y) {					// 입력값, 입력 위치 x, y
	printf("%c %d %d", KeyPressed, X, Y);
} 

void MySpecial(int key, int X, int Y) {										 // 입력값(특수문자), 입력 위치 x, y
	printf("%d %d %d \n", key, X, Y);
} 

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {			// 왼 or 오른쪽, 누름 or 해제 etc, 마우스 위치
	printf("%d %c %d %d \n", Button, State, X, Y);
	glutPostRedisplay();													// 디스플레이 강제 호출 *디스플레이 콜백함수만 가능 reshape 함수 호출 X
}

void MyMouseMove(GLint X, GLint Y) {
	printf("%d %d \n", X, Y);
}

void MyIdle() {
}

void MyTimer(int Value) {}													// 타이머 번호

void MenuProc(int entryID) {}

void MenuFunc() {}
																			// argc : 인자 수 argv : 인자
int main(int argc, char** argv) {
	glutInit(&argc, argv);													//초기화 초기설정
	//glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);							// 화면 설정 single=glFlush()
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);				// double=glutSwapBuffers()

	glutInitWindowSize(500, 500);											// 화면 크기
	glutInitWindowPosition(100, 200);										// 초기 화면 위치(시작점 좌측 상단)
	glutCreateWindow("제목");												// 그래픽창 생성
	glClearColor(1, 1, 1, 1.0);												// 색 초기화 r, g, b, 투명도 256:1 *바탕색 1,1,1=흰색 0, 0, 0 = 검정색

	glutDisplayFunc(MyDisplay);												// 콜백함수, 함수를 인자로 받고 리턴값 받음, 함수 호출 후 대기 안 함(일반 함수는 끝날 때까지 대기)

	//콜백함수 등록 시작
	glutReshapeFunc(MyReshape);
	
	/*glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecial);*/
	/*glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);*/
	//glutIdleFunc(MyIdle);													// ex)idle: cpu 쉬는 시간에 작동되는 것, 이벤트가 없을 때
	//glutTimerFunc(40, MyTimer, 1); 
	// 콜백함수 등록 끝

	//MenuFunc();															//메뉴 처리
	glutMainLoop();															// 모든 콜백함수가 끝날 때까지 기다림
	return 0;                                                                                          
}
