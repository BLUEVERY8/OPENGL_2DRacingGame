#pragma warning (disable:4996)
#include <windows.h> //윈도우는 windows.h
#include <glut.h> //윈도우는 glut.h, glu.h, gl.h
#include <glu.h> 
#include <gl.h> 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//게임화면상태, 게임 속도, 점수, 차량 스피드, 부스터 지속시간, 부스터 상태, 부스터 등장, 부스터 확률
int isGaming = 0, FPS = 50, score = 0, speed = 1, i = 0, boosterFlag = 0, isBoosting = 0, randomBooster;
int over = 0;
// 맵
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;
//차량 x 인덱스
int lrIndex = 0;

//장애물 차량 , 장애물 차량 인덱스
int comingCar1 = 0;
int cCar1Index = 0;
int comingCar2 = 35;
int cCar2Index = 0;
int comingCar3 = 70;
int cCar3Index = 0;
int randomCar1;

// 라이프
GLfloat life1 = 1, life2 = 1, life3 = 1;
int delay = 8;
int crash = 0;

// 차량 색
int carColor;
// 코인
int coin1 = 0, coin2 = 10, coin3 = 20, coin4 = 30, coin5 = 40;
int coinIdx1 = 0, coinIdx2 = 0, coinIdx3 = 0, coinIdx4 = 0, coinIdx5 = 0;
int booster = 0;
int boosterIdx = 0;

//글자 폰트
void* font1 = GLUT_BITMAP_TIMES_ROMAN_24;
void* font2 = GLUT_BITMAP_HELVETICA_18;
void* font3 = GLUT_BITMAP_8_BY_13;
// 점수 저장 버퍼
char buffer1[50], buffer2[50];
//화면에 글자 출력
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
    roadDivTop -= speed;
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



    roadDivMdl -= speed;
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
    roadDivBtm -= speed;
    if (roadDivBtm < -20) {
        roadDivBtm = 100;
        score++;
    }
    // 점수판
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(80, 97);
    glVertex2f(100, 97);
    glVertex2f(100, 98 - 8);
    glVertex2f(80, 98 - 8);
    glEnd();

    sprintf(buffer1, "SCORE: %d", score);
    glColor3f(0.0f, 1.0f, 0.0f);
    renderBitmapString(80.5, 95, (void*)font3, buffer1);
    
    // 라이프
    glColor3f(life1, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(81.5 + 2.5, 93);
    glVertex2f(82 + 2.5, 92.5);
    glVertex2f(83 + 2.5, 93);
    glVertex2f(83.5 + 2.5, 92.5);
    glVertex2f(83 + 2.5, 92);
    glVertex2f(82 + 2.5, 91.5);
    glVertex2f(81.5 + 2.5, 92);
    glVertex2f(81 + 2.5, 92.5);
    glEnd();

    glColor3f(life2, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(81.5 + 7.5, 93);
    glVertex2f(82 + 7.5, 92.5);
    glVertex2f(83 + 7.5, 93);
    glVertex2f(83.5 + 7.5, 92.5);
    glVertex2f(83 + 7.5, 92);
    glVertex2f(82 + 7.5, 91.5);
    glVertex2f(81.5 + 7.5, 92);
    glVertex2f(81 + 7.5, 92.5);
    glEnd();

    glColor3f(life3, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(81.5 + 12.5, 93);
    glVertex2f(82 + 12.5, 92.5);
    glVertex2f(83 + 12.5, 93);
    glVertex2f(83.5 + 12.5, 92.5);
    glVertex2f(83 + 12.5, 92);
    glVertex2f(82 + 12.5, 91.5);
    glVertex2f(81.5 + 12.5, 92);
    glVertex2f(81 + 12.5, 92.5);
    glEnd();

    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26 - 2, 5);
    glVertex2f(lrIndex + 26 - 2, 7);
    glVertex2f(lrIndex + 30 + 2, 7);
    glVertex2f(lrIndex + 30 + 2, 5);
    glEnd();
    //Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26 - 2, 1);
    glVertex2f(lrIndex + 26 - 2, 3);
    glVertex2f(lrIndex + 30 + 2, 3);
    glVertex2f(lrIndex + 30 + 2, 1);
    glEnd();
    //Car Body
    if (carColor == 3) {
        glColor3f(0.0f,0.0f, 1.0f);
    }
    else if (carColor == 2) {
        glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if (carColor == 1) {
        glColor3f(1.0f, 0.0f, 0.0f);
    }
    else
    glColor3f(0.678, 1.000, 0.184);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26, 1);
    glVertex2f(lrIndex + 26, 8);
    glColor3f(0.000, 0.545, 0.545);

    glVertex2f(lrIndex + 28, 10);
    glVertex2f(lrIndex + 30, 8);
    glVertex2f(lrIndex + 30, 1);
    glEnd();


    // 장애물 차량 1번
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(cCar1Index + 26 - 2, comingCar1 + 100 - 4);
    glVertex2f(cCar1Index + 26 - 2, comingCar1 + 100 - 6);
    glVertex2f(cCar1Index + 30 + 2, comingCar1 + 100 - 6);
    glVertex2f(cCar1Index + 30 + 2, comingCar1 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(cCar1Index + 26 - 2, comingCar1 + 100);
    glVertex2f(cCar1Index + 26 - 2, comingCar1 + 100 - 2);
    glVertex2f(cCar1Index + 30 + 2, comingCar1 + 100 - 2);
    glVertex2f(cCar1Index + 30 + 2, comingCar1 + 100);
    glEnd();
    glColor3f(1.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(cCar1Index + 26, comingCar1 + 100);
    glVertex2f(cCar1Index + 26, comingCar1 + 100 - 7);
    glVertex2f(cCar1Index + 28, comingCar1 + 100 - 9);
    glVertex2f(cCar1Index + 30, comingCar1 + 100 - 7);
    glVertex2f(cCar1Index + 30, comingCar1 + 100);
    glEnd();
    if (speed == 1)
        comingCar1--;
    else
        comingCar1 -= speed;
    if (comingCar1 < -100) {
        comingCar1 = 0;
        cCar1Index = rand() % 55;
    } 

    // 장애물 차량 1번에 부딪혔는지 체크
    if ((abs(lrIndex - cCar1Index) < 8) && (comingCar1 + 100 < 10)) {
        if ((life1 == 0) && (life2 == 0) && (life3 == 0)) {
            isGaming = 2;
        }
        life3 = 0;
        over = 1;

    }
    // 장애물 차량 2번
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(cCar2Index + 26 - 2, comingCar2 + 100 - 4);
    glVertex2f(cCar2Index + 26 - 2, comingCar2 + 100 - 6);
    glVertex2f(cCar2Index + 30 + 2, comingCar2 + 100 - 6);
    glVertex2f(cCar2Index + 30 + 2, comingCar2 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(cCar2Index + 26 - 2, comingCar2 + 100);
    glVertex2f(cCar2Index + 26 - 2, comingCar2 + 100 - 2);
    glVertex2f(cCar2Index + 30 + 2, comingCar2 + 100 - 2);
    glVertex2f(cCar2Index + 30 + 2, comingCar2 + 100);
    glEnd();
    glColor3f(0.294, 0.000, 0.510);
    glBegin(GL_POLYGON);
    glVertex2f(cCar2Index + 26, comingCar2 + 100);
    glVertex2f(cCar2Index + 26, comingCar2 + 100 - 7);
    glVertex2f(cCar2Index + 28, comingCar2 + 100 - 9);
    glVertex2f(cCar2Index + 30, comingCar2 + 100 - 7);
    glVertex2f(cCar2Index + 30, comingCar2 + 100);
    glEnd();
    if (speed == 1)
        comingCar2--;
    else
        comingCar2 -= speed;
    if (comingCar2 < -100) {
        comingCar2 = 0;
        cCar2Index = rand() % 55;
    }
    // 장애물 차량 2번에 부딪혔는지 체크
    if ((abs(lrIndex - cCar2Index) < 8) && (comingCar2 + 100 < 10)) {
        if ((life1 == 0) && (life2 == 0) && (life3 == 0)) {
            isGaming = 2;
        }
        life2 = 0;
        over = 1;
    }


    // 장애물 차량 3번
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(cCar3Index + 26 - 2, comingCar3 + 100 - 4);
    glVertex2f(cCar3Index + 26 - 2, comingCar3 + 100 - 6);
    glVertex2f(cCar3Index + 30 + 2, comingCar3 + 100 - 6);
    glVertex2f(cCar3Index + 30 + 2, comingCar3 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(cCar3Index + 26 - 2, comingCar3 + 100);
    glVertex2f(cCar3Index + 26 - 2, comingCar3 + 100 - 2);
    glVertex2f(cCar3Index + 30 + 2, comingCar3 + 100 - 2);
    glVertex2f(cCar3Index + 30 + 2, comingCar3 + 100);
    glEnd();
    glColor3f(1.000, 0.271, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(cCar3Index + 26, comingCar3 + 100);
    glVertex2f(cCar3Index + 26, comingCar3 + 100 - 7);
    glVertex2f(cCar3Index + 28, comingCar3 + 100 - 9);
    glVertex2f(cCar3Index + 30, comingCar3 + 100 - 7);
    glVertex2f(cCar3Index + 30, comingCar3 + 100);
    glEnd();
    if (speed == 1)
        comingCar3--;
    else
        comingCar3 -= speed;
    if (comingCar3 < -100) {
        comingCar3 = 0;
        cCar3Index = rand() % 55;
    }
    // 장애물 차량 3번에 부딪혔는지 체크
    if ((abs(lrIndex - cCar3Index) < 8) && (comingCar3 + 100 < 10)) {

        if ((life1 == 0) && (life2 == 0) && (life3 == 0)) {
            isGaming = 2;
        }
        life1 = 0;
        over = 1;

    }

    //코인(점수증가)
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(coinIdx1 + 28, coin1 + 100 - 2);
    glVertex2f(coinIdx1 + 26, coin1 + 100 - 6);
    glVertex2f(coinIdx1 + 30, coin1 + 100 - 6);

    glEnd();
    coin1 -= speed; //코인 이동
    // 코인 획득 감지
    if ((abs(lrIndex - coinIdx1) < 8) && (coin1 + 100 < 10)) {
        score += 3;
        coinIdx1 = rand() % 45;
        coin1 = 0;
    }
    //코인 재생성
    else if (coin1 < -100)
    {
        coinIdx1 = rand() % 45;
        coin1 = 0;
    }

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(coinIdx2 + 28, coin2 + 100 - 2);
    glVertex2f(coinIdx2 + 26, coin2 + 100 - 6);
    glVertex2f(coinIdx2 + 30, coin2 + 100 - 6);

    glEnd();
    coin2 -= speed;
    if ((abs(lrIndex - coinIdx2) < 8) && (coin2 + 100 < 10)) {
        score += 3;
        coinIdx2 = rand() % 45;
        coin2 = 0;
    }
    else if (coin2 < -100)
    {
        coinIdx2 = rand() % 45;
        coin2 = 0;
    }

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(coinIdx3 + 28, coin3 + 100 - 2);
    glVertex2f(coinIdx3 + 26, coin3 + 100 - 6);
    glVertex2f(coinIdx3 + 30, coin3 + 100 - 6);

    glEnd();
    coin3 -= speed;
    if ((abs(lrIndex - coinIdx3) < 8) && (coin3 + 100 < 10)) {
        score += 3;
        coinIdx3 = rand() % 45;
        coin3 = 0;
    }
    else if (coin3 < -100)
    {
        coinIdx3 = rand() % 45;
        coin3 = 0;
    }

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(coinIdx4 + 28, coin4 + 100 - 2);
    glVertex2f(coinIdx4 + 26, coin4 + 100 - 6);
    glVertex2f(coinIdx4 + 30, coin4 + 100 - 6);

    glEnd();
    coin4 -= speed;
    if ((abs(lrIndex - coinIdx4) < 8) && (coin4 + 100 < 10)) {
        score += 3;
        coinIdx4 = rand() % 45;
        coin4 = 0;
    }
    else if (coin4 < -100)
    {
        coinIdx4 = rand() % 45;
        coin4 = 0;
    }

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(coinIdx5 + 28, coin5 + 100 - 2);
    glVertex2f(coinIdx5 + 26, coin5 + 100 - 6);
    glVertex2f(coinIdx5 + 30, coin5 + 100 - 6);

    glEnd();
    coin5 -= speed;
    if ((abs(lrIndex - coinIdx5) < 8) && (coin5 + 100 < 10)) {
        score += 3;
        coinIdx5 = rand() % 45;
        coin5 = 0;
    }
    else if (coin5 < -100)
    {
        coinIdx5 = rand() % 45;
        coin5 = 0;
    }
    //부스터(속도 증가)
    //부스터 확률 설정
    if (isBoosting == 0)
    {
        randomBooster = rand() % 20;
    }
    //20분의 1 확률로 부스터 생성
    if (randomBooster == 8)
    {
        isBoosting = 1;
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POLYGON);
        glVertex2f(boosterIdx + 28, booster + 100);
        glVertex2f(boosterIdx + 26, booster + 100 - 2);
        glVertex2f(boosterIdx + 27, booster + 100 - 2);
        glVertex2f(boosterIdx + 27, booster + 100 - 6);
        glVertex2f(boosterIdx + 29, booster + 100 - 6);
        glVertex2f(boosterIdx + 29, booster + 100 - 2);
        glVertex2f(boosterIdx + 30, booster + 100 - 2);
        glEnd();
        if (speed == 1)
            booster--;
        else
            booster -= speed;
        //부스터 획득 감지
        if ((abs(lrIndex - boosterIdx) < 8) && (booster + 100 < 10)) {
            speed = 3;
            boosterIdx = rand() % 45;
            booster = 0;
            isBoosting = 0;
            boosterFlag = 1;
        }
        else if (booster < -100)
        {
            boosterIdx = rand() % 45;
            booster = 0;
            isBoosting = 0;
        }
    }


}

void NewMenu() {
    // 게임이 끝났을 때 나오는 메뉴
    if (over == 1) {
        glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(32 - 4, 35);
        glVertex2f(32 + 46, 35);
        glVertex2f(32 + 46, 15);
        glVertex2f(32 - 4, 15);
        glEnd();

        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(32 - 4, 35);
        glVertex2f(32 + 46, 35);
        glVertex2f(32 + 46, 34);
        glVertex2f(32 - 4, 34);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(32 + 45, 35);
        glVertex2f(32 + 46, 35);
        glVertex2f(32 + 46, 15);
        glVertex2f(32 + 45, 15);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(32 - 4, 16);
        glVertex2f(32 + 46, 16);
        glVertex2f(32 + 46, 15);
        glVertex2f(32 - 4, 15);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(32 - 4, 35);
        glVertex2f(32 - 5, 35);
        glVertex2f(32 - 5, 15);
        glVertex2f(32 - 4, 15);
        glEnd();
        glColor3f(1.0, 0.0, 0.0);
        renderBitmapString(15, 70, (void*)font2, "GAME OVER");
        glColor3f(1.0, 0.0, 0.0);
        sprintf(buffer2, "Score : %d", score);
        renderBitmapString(15, 60, (void*)font2, buffer2);
        glColor3f(0.0f, 0.0f, 0.0f);
        renderBitmapString(15, 50, (void*)font2, "If you want to restart game Press space bar");
        glColor3f(1.0f, 1.0f, 1.0f);
        renderBitmapString(40, 85, (void*)font2, "The racer");

        glColor3f(0.0f, 1.0f, 0.0f);
        renderBitmapString(30, 30, (void*)font2, "Press SPACE to START");

        glColor3f(1.0f, 1.0f, 1.0f);
        renderBitmapString(30, 20, (void*)font3, "Press RIGHT to turn Right");
        renderBitmapString(30, 18, (void*)font3, "Press LEFT to turn Left");

    }
    // 기본 메뉴 창
    else {
        glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(28-7, 65 + 2.5);
        glVertex2f(78+7, 65 + 2.5);
        glVertex2f(78+7, 45 - 2.5);
        glVertex2f(28-7, 45 - 2.5);
        glEnd();

        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(28-7, 65+2.5);
        glVertex2f(78+7, 65 + 2.5);
        glVertex2f(78+7, 64 + 2.5);
        glVertex2f(28-7, 64 + 2.5);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(77 + 7, 65 + 2.5);
        glVertex2f(78 + 7, 65 + 2.5);
        glVertex2f(78 + 7, 45 - 2.5);
        glVertex2f(77 + 7, 45 - 2.5);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(28-7, 46 - 2.5);
        glVertex2f(78+7, 46 - 2.5);
        glVertex2f(78+7, 45 - 2.5);
        glVertex2f(28-7, 45 - 2.5);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(28-7, 65 + 2.5);
        glVertex2f(27-7, 65 + 2.5);
        glVertex2f(27-7, 45 - 2.5);
        glVertex2f(28-7, 45 - 2.5);
        glEnd();


        glColor3f(1.0f, 1.0f, 0.0f);
        renderBitmapString(40, 85, font1, "The racer");

        glColor3f(0.0f, 1.0f, 0.0f);
        renderBitmapString(30, 60, font2, "Press SPACE to START");

        glColor3f(1.0f, 1.0f, 1.0f);
        renderBitmapString(27, 50, font3, "Press RIGHT to turn Right");
        renderBitmapString(27, 48, font3, "Press LEFT to turn Left");
        renderBitmapString(27, 46, font3, "Click Right Button to Change Color");
    }
}

void startMenu()
{
    //시작 화면
    if (isGaming == 1)
        startGame();
    //종료 화면
    else
        NewMenu();

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
void myTimer(int value)
{
    if (value == 0)
    {
        i++; //부스터 지속시간 측정
        if (i == 500)
            speed = 1;
        if (boosterFlag == 1)
        {
            boosterFlag = 0;
            glutPostRedisplay();
            glutTimerFunc(1000 / FPS, myTimer, 1);
        }
        else
        {
            glutPostRedisplay();
            glutTimerFunc(1000 / FPS, myTimer, 0);
        }
    }
    //부스터 감지 후 지속 시간 설정
    else if (value == 1)
    {
        i = 0;
        glutPostRedisplay();
        glutTimerFunc(1000 / FPS, myTimer, 0);

    }

}

void mySpecialKey(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
    {
        if (lrIndex <= 44) {
            lrIndex = lrIndex + (FPS / 10);
            if (lrIndex > 44) {
                lrIndex = 45;
            }
        }
    }
    else if (key == GLUT_KEY_LEFT)
    {
        if (lrIndex >= 0) {
            lrIndex = lrIndex - (FPS / 10);
            if (lrIndex < 0) {
                lrIndex = -1;
            }
        }
    }
}
void myKey(unsigned char key, int x, int y)
{
    if (isGaming == 0 || isGaming == 2)
    {
        if (key == 32)
        {
            score = 0, speed = 1, i = 0, boosterFlag = 0, isBoosting = 0;
            //int over = 0;

            lrIndex = 0;

            //장애물 차량 , 장애물 차량 인덱스
            comingCar1 = 0;
            comingCar2 = 35;
            comingCar3 = 70;


            //Car Coming
            coin1 = 0, coin2 = 10, coin3 = 20, coin4 = 30, coin5 = 40;
            coinIdx1 = 0, coinIdx2 = 0, coinIdx3 = 0, coinIdx4 = 0, coinIdx5 = 0;
            booster = 0;
            boosterIdx = 0;
            coinIdx1 = rand() % 45;
            coinIdx2 = rand() % 45;
            coinIdx3 = rand() % 45;
            coinIdx4 = rand() % 45;
            coinIdx5 = rand() % 45;
            isGaming = 1;
            over = 0;
            life1 = 1; life2 = 1; life3 = 1;
            glutPostRedisplay();
        }

    }
    glutPostRedisplay();
}
void init()
{
    glOrtho(0, 100, 0, 100, -1, 1);
    glClearColor(0.184, 0.310, 0.310, 1);
}

void MenuProc(int entryID) {
    if (entryID == 3) {
        carColor = entryID;
        printf("선택한 차량색 => Blue\n");
    }
    else if (entryID == 2) { 
        carColor = entryID; 
        printf("선택한 차량색 => Green\n");
    }
    else if (entryID == 1) {
        carColor = entryID;
        printf("선택한 차량색 => Red\n");
    }
    glutPostRedisplay();
}

void MenuFunc() {
    GLint MyMainMenuID = glutCreateMenu(MenuProc);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 650);
    glutInitWindowPosition(200, 20);
    glutCreateWindow("The racer");
    init();
    srand((unsigned int)time(NULL));
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(mySpecialKey);
    glutKeyboardFunc(myKey);
    glutTimerFunc(1000, myTimer, 0);
    MenuFunc();

    glutMainLoop();

    return 0;
}