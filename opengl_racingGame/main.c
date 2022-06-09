#pragma warning (disable:4996)
#include <windows.h>
#include <glut.h> 
#include <glu.h>
#include <gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <time.h>

// ����
#define _C 1046.502
#define CoinSound "F:\\�б� ����\\��ǻ�ͱ׷��Ƚ�\\localRepo\\TeamProject\\opengl_racingGame\\BGM\\CoinSound.wav"

//����ȭ�����, ���� �ӵ�, ����, ���� ���ǵ�, �ν��� ���ӽð�, �ν��� ����, �ν��� ����, �ν��� Ȯ��
int isGaming = 0, FPS = 50, score = 0, speed = 1, i = 0, isBoosting = 0, createBoost = 0, randomBooster;
int isCrash = 0, delay = 0;
// ��
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;
//���� x �ε���
int lrIndex = 0;

//��ֹ� ���� , ��ֹ� ���� �ε���
int comingCar1 = 0;
int cCar1Index = 0;
int comingCar2 = 35;
int cCar2Index = 0;
int comingCar3 = 70;
int cCar3Index = 0;
int randomCar1;

// ������
GLfloat life1 = 1, life2 = 1, life3 = 1;
int lifeIndex = 80;
// ���� ��
int carColor;
const GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat black[] = { 0.8, 0.8, 0.8, 1.0 };
const GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
const GLfloat polished[] = { 100.0 };
// ����
int coin1 = 0, coin2 = 10, coin3 = 20, coin4 = 30, coin5 = 40;
int randomcoin = 0;
int coinIdx1 = 0, coinIdx2 = 0, coinIdx3 = 0, coinIdx4 = 0, coinIdx5 = 0;
int coin1score = 0, coin2score = 0, coin3score = 0, coin4score = 0, coin5score = 0;
int booster = 0;
int boosterIdx = 0;

//���� ��Ʈ
void* font1 = GLUT_BITMAP_TIMES_ROMAN_24;
void* font2 = GLUT_BITMAP_HELVETICA_18;
void* font3 = GLUT_BITMAP_8_BY_13;
// ���� ���� ����
char buffer1[50], buffer2[50];
//플레이 횟수
int play = 0;
//저장할 이름, 점수
char* player[10][10], record[10];
//ȭ�鿡 ���� ���
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
    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glMaterialfv(GL_FRONT, GL_SHININESS, polished);
    //glColor3f(0.412, 0.412, 0.412);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
    glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
    glMaterialfv(GL_FRONT, GL_SHININESS, polished);

    //Road Middel Border
      //TOP
    glColor3f(1.0f, 1.0f, 0.0f);
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
    glColor3f(1.0f, 1.0f, 0.0f);
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
    glColor3f(1.0f, 1.0f, 0.0f);
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
    glDisable(GL_LIGHTING);
    //Road Left Border
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(23, 100);
    glVertex2f(23, 0);
    glEnd();

    //Road Right Border
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(77, 0);
    glVertex2f(77, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();

    

    // ������
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

    // ������
    glColor3f(life1, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(lifeIndex + 4, 93);
    glVertex2f(lifeIndex + 4.5, 92.5);
    glVertex2f(lifeIndex + 5.5, 93);
    glVertex2f(lifeIndex + 6, 92.5);
    glVertex2f(lifeIndex + 5.5, 92);
    glVertex2f(lifeIndex + 4.5, 91.5);
    glVertex2f(lifeIndex + 4, 92);
    glVertex2f(lifeIndex + 3.5, 92.5);
    glEnd();

    glColor3f(life2, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(lifeIndex + 9, 93);
    glVertex2f(lifeIndex + 9.5, 92.5);
    glVertex2f(lifeIndex + 10.5, 93);
    glVertex2f(lifeIndex + 11, 92.5);
    glVertex2f(lifeIndex + 10.5, 92);
    glVertex2f(lifeIndex + 9.5, 91.5);
    glVertex2f(lifeIndex + 9, 92);
    glVertex2f(lifeIndex + 8.5, 92.5);
    glEnd();

    glColor3f(life3, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(lifeIndex + 14, 93);
    glVertex2f(lifeIndex + 14.5, 92.5);
    glVertex2f(lifeIndex + 15.5, 93);
    glVertex2f(lifeIndex + 16, 92.5);
    glVertex2f(lifeIndex + 15.5, 92);
    glVertex2f(lifeIndex + 14.5, 91.5);
    glVertex2f(lifeIndex + 14, 92);
    glVertex2f(lifeIndex + 13.5, 92.5);
    glEnd();

    //코인(점수증가)
    randomcoin = rand() % 40;

    //1번 코인
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(coinIdx1 + 26, coin1 + 98);
    glVertex2f(coinIdx1 + 29, coin1 + 98);
    glVertex2f(coinIdx1 + 31, coin1 + 96);
    glVertex2f(coinIdx1 + 31, coin1 + 94);
    glVertex2f(coinIdx1 + 29, coin1 + 92);
    glVertex2f(coinIdx1 + 26, coin1 + 92);
    glVertex2f(coinIdx1 + 24, coin1 + 94);
    glVertex2f(coinIdx1 + 24, coin1 + 96);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(coinIdx1 + 25, coin1 + 95 - 1);
    glVertex2f(coinIdx1 + 25, coin1 + 97 - 1);
    glVertex2f(coinIdx1 + 26, coin1 + 98 - 1);
    glVertex2f(coinIdx1 + 29, coin1 + 98 - 1);
    glVertex2f(coinIdx1 + 29, coin1 + 97 - 1);
    glVertex2f(coinIdx1 + 26, coin1 + 97 - 1);
    glVertex2f(coinIdx1 + 26, coin1 + 95 - 1);
    glVertex2f(coinIdx1 + 29, coin1 + 95 - 1);
    glVertex2f(coinIdx1 + 29, coin1 + 94 - 1);
    glVertex2f(coinIdx1 + 26, coin1 + 94 - 1);
    glEnd();

    coin1 -= speed; //코인 이동
    // 코인 획득 감지
    if ((abs(lrIndex - coinIdx1) < 8) && (coin1 + 100 < 12)) {
        if (coin1score == 0) {
            score += 3;
            coin1score = 1;
            coin1 = -100;
        }
        if (randomcoin == 1 && coin1 < -100) {
            coinIdx1 = rand() % 45;
            coin1 = 6;
            coin1score = 0;
        }
    }
    //코인 재생성
    else if (coin1 < -100)
    {
        coinIdx1 = rand() % 45;
        if (randomcoin == 1)
            coin1 = 0;
    }

    //2번 코인
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(coinIdx2 + 26, coin2 + 98);
    glVertex2f(coinIdx2 + 29, coin2 + 98);
    glVertex2f(coinIdx2 + 31, coin2 + 96);
    glVertex2f(coinIdx2 + 31, coin2 + 94);
    glVertex2f(coinIdx2 + 29, coin2 + 92);
    glVertex2f(coinIdx2 + 26, coin2 + 92);
    glVertex2f(coinIdx2 + 24, coin2 + 94);
    glVertex2f(coinIdx2 + 24, coin2 + 96);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(coinIdx2 + 25, coin2 + 95 - 1);
    glVertex2f(coinIdx2 + 25, coin2 + 97 - 1);
    glVertex2f(coinIdx2 + 26, coin2 + 98 - 1);
    glVertex2f(coinIdx2 + 29, coin2 + 98 - 1);
    glVertex2f(coinIdx2 + 29, coin2 + 97 - 1);
    glVertex2f(coinIdx2 + 26, coin2 + 97 - 1);
    glVertex2f(coinIdx2 + 26, coin2 + 95 - 1);
    glVertex2f(coinIdx2 + 29, coin2 + 95 - 1);
    glVertex2f(coinIdx2 + 29, coin2 + 94 - 1);
    glVertex2f(coinIdx2 + 26, coin2 + 94 - 1);
    glEnd();
    coin2 -= speed;
    if ((abs(lrIndex - coinIdx2) < 8) && (coin2 + 100 < 12)) {
        if (coin2score == 0) {
            score += 3;
            coin2score = 1;
            coin2 = -100;
        }
        if (randomcoin == 2 && coin2 < -100) {
            coinIdx2 = rand() % 45;
            coin2 = 6;
            coin2score = 0;
        }
    }
    else if (coin2 < -100)
    {
        coinIdx2 = rand() % 45;
        if (randomcoin == 2)
            coin2 = 0;
    }
    //3번 코인
    glColor3f(0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(coinIdx3 + 26, coin3 + 98);
    glVertex2f(coinIdx3 + 29, coin3 + 98);
    glVertex2f(coinIdx3 + 31, coin3 + 96);
    glVertex2f(coinIdx3 + 31, coin3 + 94);
    glVertex2f(coinIdx3 + 29, coin3 + 92);
    glVertex2f(coinIdx3 + 26, coin3 + 92);
    glVertex2f(coinIdx3 + 24, coin3 + 94);
    glVertex2f(coinIdx3 + 24, coin3 + 96);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(coinIdx3 + 25, coin3 + 95 - 1);
    glVertex2f(coinIdx3 + 25, coin3 + 97 - 1);
    glVertex2f(coinIdx3 + 26, coin3 + 98 - 1);
    glVertex2f(coinIdx3 + 29, coin3 + 98 - 1);
    glVertex2f(coinIdx3 + 29, coin3 + 97 - 1);
    glVertex2f(coinIdx3 + 26, coin3 + 97 - 1);
    glVertex2f(coinIdx3 + 26, coin3 + 95 - 1);
    glVertex2f(coinIdx3 + 29, coin3 + 95 - 1);
    glVertex2f(coinIdx3 + 29, coin3 + 94 - 1);
    glVertex2f(coinIdx3 + 26, coin3 + 94 - 1);
    glEnd();
    coin3 -= speed;
    if ((abs(lrIndex - coinIdx3) < 8) && (coin3 + 100 < 12)) {
        if (coin3score == 0) {
            score += 3;
            coin3score = 1;
            coin3 = -100;
        }
        if (randomcoin == 3 && coin3 < -100) {
            coinIdx3 = rand() % 45;
            coin3 = 6;
            coin3score = 0;
        }
    }
    else if (coin3 < -100)
    {
        coinIdx3 = rand() % 45;
        if (randomcoin == 3)
            coin3 = 0;
    }
    //4번 코인
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(coinIdx4 + 26, coin4 + 98);
    glVertex2f(coinIdx4 + 29, coin4 + 98);
    glVertex2f(coinIdx4 + 31, coin4 + 96);
    glVertex2f(coinIdx4 + 31, coin4 + 94);
    glVertex2f(coinIdx4 + 29, coin4 + 92);
    glVertex2f(coinIdx4 + 26, coin4 + 92);
    glVertex2f(coinIdx4 + 24, coin4 + 94);
    glVertex2f(coinIdx4 + 24, coin4 + 96);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(coinIdx4 + 25, coin4 + 95 - 1);
    glVertex2f(coinIdx4 + 25, coin4 + 97 - 1);
    glVertex2f(coinIdx4 + 26, coin4 + 98 - 1);
    glVertex2f(coinIdx4 + 29, coin4 + 98 - 1);
    glVertex2f(coinIdx4 + 29, coin4 + 97 - 1);
    glVertex2f(coinIdx4 + 26, coin4 + 97 - 1);
    glVertex2f(coinIdx4 + 26, coin4 + 95 - 1);
    glVertex2f(coinIdx4 + 29, coin4 + 95 - 1);
    glVertex2f(coinIdx4 + 29, coin4 + 94 - 1);
    glVertex2f(coinIdx4 + 26, coin4 + 94 - 1);
    glEnd();
    coin4 -= speed;
    if ((abs(lrIndex - coinIdx4) < 8) && (coin4 + 100 < 12)) {
        if (coin4score == 0) {
            score += 3;
            coin4score = 1;
            coin4 = -100;
        }
        if (randomcoin == 4 && coin4 < -100) {
            coinIdx4 = rand() % 45;
            coin4 = 6;
            coin4score = 0;
        }
    }
    else if (coin4 < -100)
    {
        coinIdx4 = rand() % 45;
        if (randomcoin == 4)
            coin4 = 0;
    }
    //5번 코인
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(coinIdx5 + 26, coin5 + 98);
    glVertex2f(coinIdx5 + 29, coin5 + 98);
    glVertex2f(coinIdx5 + 31, coin5 + 96);
    glVertex2f(coinIdx5 + 31, coin5 + 94);
    glVertex2f(coinIdx5 + 29, coin5 + 92);
    glVertex2f(coinIdx5 + 26, coin5 + 92);
    glVertex2f(coinIdx5 + 24, coin5 + 94);
    glVertex2f(coinIdx5 + 24, coin5 + 96);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(coinIdx5 + 25, coin5 + 95 - 1);
    glVertex2f(coinIdx5 + 25, coin5 + 97 - 1);
    glVertex2f(coinIdx5 + 26, coin5 + 98 - 1);
    glVertex2f(coinIdx5 + 29, coin5 + 98 - 1);
    glVertex2f(coinIdx5 + 29, coin5 + 97 - 1);
    glVertex2f(coinIdx5 + 26, coin5 + 97 - 1);
    glVertex2f(coinIdx5 + 26, coin5 + 95 - 1);
    glVertex2f(coinIdx5 + 29, coin5 + 95 - 1);
    glVertex2f(coinIdx5 + 29, coin5 + 94 - 1);
    glVertex2f(coinIdx5 + 26, coin5 + 94 - 1);

    glEnd();
    coin5 -= speed;
    if ((abs(lrIndex - coinIdx5) < 8) && ((coin5 + 100) < 12)) {
        if (coin5score == 0) {
            score += 3;
            coin5score = 1;
            coin5 = -100;
        }
        if (randomcoin == 5 && coin5 < -100) {
            coinIdx5 = rand() % 45;
            coin5 = 6;
            coin5score = 0;
        }
    }
    else if (coin5 < -100)
    {
        coinIdx5 = rand() % 45;
        if (randomcoin == 5)
            coin5 = 0;
    }

    // 부스터
    // 부스터 생성 확률
    if (createBoost == 0)
    {
        randomBooster = rand() % 20;
    }
    //부스터 생성
    if (randomBooster == 8)
    {
        createBoost = 1;
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
        //부스터 획득시
        if ((abs(lrIndex - boosterIdx) < 8) && (booster + 100 < 10)) {
            speed = 3;
            boosterIdx = rand() % 45;
            booster = 0;
            createBoost = 0;
            isBoosting = 1;
        }
        else if (booster < -100)
        {
            boosterIdx = rand() % 45;
            booster = 0;
            createBoost = 0;
        }
    }
    // 장애물
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(cCar1Index + 26 - 2, comingCar1 + 100 - 4);
    glVertex2f(cCar1Index + 26 - 2, comingCar1 + 100 - 6);
    glVertex2f(cCar1Index + 30 + 2, comingCar1 + 100 - 6);
    glVertex2f(cCar1Index + 30 + 2, comingCar1 + 100 - 4);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(cCar1Index + 26 - 2, comingCar1 + 100);
    glVertex2f(cCar1Index + 26 - 2, comingCar1 + 100 - 2);
    glVertex2f(cCar1Index + 30 + 2, comingCar1 + 100 - 2);
    glVertex2f(cCar1Index + 30 + 2, comingCar1 + 100);
    glEnd();
    glColor3f(1.0f, 0.0f, 0.0f);
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
        cCar1Index = rand() % 45;
    }
    delay++;
    if (isBoosting == 0)
    {
        if (delay > 10)
        {
            isCrash = 0;
            delay = 0;
        }
    }
    else
    {
        if (delay > 4)
        {
            isCrash = 0;
            delay = 0;
        }
    }

    // ��ֹ� ���� 1���� �ε������� üũ
    if (isCrash == 0)
    {
        if ((abs(lrIndex - cCar1Index) < 8) && (comingCar1 + 100 < 10)) {
            if ((life1 == 1) && (life2 == 1) && (life3 == 1)) {
                life3 = 0;
            }
            else if ((life1 == 1) && (life2 == 1) && (life3 == 0)) {
                life2 = 0;
            }
            else if ((life1 == 1) && (life2 == 0) && (life3 == 0)) {
                life1 = 0;
            }
            if ((life1 == 0) && (life2 == 0) && (life3 == 0)) {
                isGaming = 2;
            }
            isCrash = 1;
            delay = 0;
        }
    }

    // ��ֹ� ���� 2��
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(cCar2Index + 26 - 2, comingCar2 + 100 - 4);
    glVertex2f(cCar2Index + 26 - 2, comingCar2 + 100 - 6);
    glVertex2f(cCar2Index + 30 + 2, comingCar2 + 100 - 6);
    glVertex2f(cCar2Index + 30 + 2, comingCar2 + 100 - 4);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(cCar2Index + 26 - 2, comingCar2 + 100);
    glVertex2f(cCar2Index + 26 - 2, comingCar2 + 100 - 2);
    glVertex2f(cCar2Index + 30 + 2, comingCar2 + 100 - 2);
    glVertex2f(cCar2Index + 30 + 2, comingCar2 + 100);
    glEnd();
    glColor3f(0.294, 0.0f, 0.510);
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
        cCar2Index = rand() % 45;
    }
    // ��ֹ� ���� 2���� �ε������� üũ
    if (isCrash == 0)
    {
        if ((abs(lrIndex - cCar2Index) < 8) && (comingCar2 + 100 < 10)) {
            if ((life1 == 1) && (life2 == 1) && (life3 == 1)) {
                life3 = 0;
            }
            else if ((life1 == 1) && (life2 == 1) && (life3 == 0)) {
                life2 = 0;
            }
            else if ((life1 == 1) && (life2 == 0) && (life3 == 0)) {
                life1 = 0;
            }
            if ((life1 == 0) && (life2 == 0) && (life3 == 0)) {
                isGaming = 2;
            }
            isCrash = 1;
            delay = 0;
        }
    }


    // ��ֹ� ���� 3��
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(cCar3Index + 26 - 2, comingCar3 + 100 - 4);
    glVertex2f(cCar3Index + 26 - 2, comingCar3 + 100 - 6);
    glVertex2f(cCar3Index + 30 + 2, comingCar3 + 100 - 6);
    glVertex2f(cCar3Index + 30 + 2, comingCar3 + 100 - 4);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(cCar3Index + 26 - 2, comingCar3 + 100);
    glVertex2f(cCar3Index + 26 - 2, comingCar3 + 100 - 2);
    glVertex2f(cCar3Index + 30 + 2, comingCar3 + 100 - 2);
    glVertex2f(cCar3Index + 30 + 2, comingCar3 + 100);
    glEnd();
    glColor3f(1.0f, 0.271, 0.0f);
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
        cCar3Index = rand() % 45;
    }
    // ��ֹ� ���� 3���� �ε������� üũ
    if (isCrash == 0)
    {
        if ((abs(lrIndex - cCar2Index) < 8) && (comingCar2 + 100 < 10)) {
            if ((life1 == 1) && (life2 == 1) && (life3 == 1)) {
                life3 = 0;
            }
            else if ((life1 == 1) && (life2 == 1) && (life3 == 0)) {
                life2 = 0;
            }
            else if ((life1 == 1) && (life2 == 0) && (life3 == 0)) {
                life1 = 0;
            }
            if ((life1 == 0) && (life2 == 0) && (life3 == 0)) {
                isGaming = 2;
            }
            isCrash = 1;
            delay = 0;
        }
    }

    //차량
    GLfloat light0Position[] = { 0, 5, 3, 1.0 };
    GLfloat light1Position[] = { 0, 5, 3, 1.0 };
    glPushMatrix();
    glTranslatef(lrIndex + 27, 9, 1);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, polished);
    //glColor3f(0.9, 0.9, 0.9);
    glutSolidSphere(1, 40, 40);
    glDisable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(lrIndex + 29, 9, 1);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, polished);
    //glColor3d(0.9, 0.9, 0.9);
    glutSolidSphere(1, 40, 40);
    glDisable(GL_LIGHTING);
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26 - 2, 5);
    glVertex2f(lrIndex + 26 - 2, 7);
    glVertex2f(lrIndex + 30 + 2, 7);
    glVertex2f(lrIndex + 30 + 2, 5);
    glEnd();
    //Back Tire
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26 - 2, 1);
    glVertex2f(lrIndex + 26 - 2, 3);
    glVertex2f(lrIndex + 30 + 2, 3);
    glVertex2f(lrIndex + 30 + 2, 1);
    glEnd();
    //Car Body
    if (carColor == 3) {
        glColor3f(0.0f, 0.0f, 1.0f);
    }
    else if (carColor == 2) {
        glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if (carColor == 1) {
        glColor3f(1.0f, 0.0f, 0.0f);
    }
    else
        glColor3f(0.678, 1.0f, 0.184);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26, 1);
    glVertex2f(lrIndex + 26, 8);
    glColor3f(0.0f, 0.545, 0.545);

    glVertex2f(lrIndex + 28, 10);
    glVertex2f(lrIndex + 30, 8);
    glVertex2f(lrIndex + 30, 1);
    glEnd();
}

void newMenu() {
    // ������ ������ �� ������ �޴�
    if (isGaming == 2) {
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
        renderBitmapString(30, 16, font3, "Press S to save your score");

    }
    else if (isGaming == 3)
    {
        printf("이름을 입력해주세요.예)AAA, BBB, ABC\n이름 : ");
        scanf("%s", (const char*)player[play]);
        play++;
        glColor3f(1.0, 1.0, 1.0);
        if (play == 0)
        {
            renderBitmapString(30, 50 + 10, font2, "No Record");
            renderBitmapString(30, 50 + 10 - 3, font2, "Press B to move start menu");
        }
        else if (play != 0) {
            for (int i = 0; i < play; i++)
            {
                renderBitmapString(5, 95 - (i * 2), font3, (const char*)player[i]);
                renderBitmapString(10, 95 - (i * 2), font3, buffer2);
            }
            renderBitmapString(30, 50, font2, "Press B to move start menu");
        }
    }
    // �⺻ �޴� â
    else {
        glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(28 - 7, 65 + 2.5);
        glVertex2f(78 + 7, 65 + 2.5);
        glVertex2f(78 + 7, 45 - 2.5);
        glVertex2f(28 - 7, 45 - 2.5);
        glEnd();

        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(28 - 7, 65 + 2.5);
        glVertex2f(78 + 7, 65 + 2.5);
        glVertex2f(78 + 7, 64 + 2.5);
        glVertex2f(28 - 7, 64 + 2.5);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(77 + 7, 65 + 2.5);
        glVertex2f(78 + 7, 65 + 2.5);
        glVertex2f(78 + 7, 45 - 2.5);
        glVertex2f(77 + 7, 45 - 2.5);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(28 - 7, 46 - 2.5);
        glVertex2f(78 + 7, 46 - 2.5);
        glVertex2f(78 + 7, 45 - 2.5);
        glVertex2f(28 - 7, 45 - 2.5);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(28 - 7, 65 + 2.5);
        glVertex2f(27 - 7, 65 + 2.5);
        glVertex2f(27 - 7, 45 - 2.5);
        glVertex2f(28 - 7, 45 - 2.5);
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

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (isGaming == 1)
    {
        glClearColor(0.0, 0.4, 0.0, 1);
        startGame();
    }
    else
        newMenu();
    glutSwapBuffers();
}
void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    //GLfloat widthFactor = (GLfloat)w / 300;
    //GLfloat heightFactor = (GLfloat)h / 300;

    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glOrtho(0, 100, 0, 100, -5, 5);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}
void myTimer(int value)
{
    if (value == 0)
    {
        i++; //�ν��� ���ӽð� ����
        if (i == 500)
            speed = 1;
        if (isBoosting == 1)
        {
            isBoosting = 0;
            glutPostRedisplay();
            glutTimerFunc(1000 / FPS, myTimer, 1);
        }
        else
        {
            glutPostRedisplay();
            glutTimerFunc(1000 / FPS, myTimer, 0);
        }
    }
    //�ν��� ���� �� ���� �ð� ����
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
            score = 0, speed = 1, i = 0, isBoosting = 0, createBoost = 0;
            //int over = 0;

            lrIndex = 0;

            //��ֹ� ���� , ��ֹ� ���� �ε���
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
            life1 = 1; life2 = 1; life3 = 1;
        }
        else if (key == 's' && isGaming == 2)
        {
            isGaming = 3;
        }

    }
    if (isGaming == 3)
        if (key == 'b')
            isGaming = 0;
    glutPostRedisplay();
}
void init()
{
    glOrtho(0, 100, 0, 100, -1, 1);
    glClearColor(0.184, 0.310, 0.310, 1);
}

void initLight()
{
    GLfloat light0Ambient[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat light0Diffuse[] = { 0.8, 0.7, 0.6, 1.0 };
    GLfloat light0Specular[] = { 1.0, 1.0, 1.0, 1.0 };
    //GLfloat light0Direction[] = { 0, 0, 0.0 };
    GLfloat light0Cutoff[] = { 20 };
    GLfloat materialAmbient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat materialDiffuse[] = { 0.9, 0.9, 0.9, 1.0 };
    GLfloat materialSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat materialShininess[] = { 25.0 };
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0Direction);
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, light0Cutoff);

    GLfloat light1Ambient[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat light1Diffuse[] = { 0.8, 0.7, 0.6, 1.0 };
    GLfloat light1Specular[] = { 1.0, 1.0, 1.0, 1.0 };
    //GLfloat light1Direction[] = { 0, 0, 0.0 };
    GLfloat light1Cutoff[] = { 20 };

    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light1Direction);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, light1Cutoff);
    glEnable(GL_LIGHT0); 
}
void MenuProc(int entryID) {
    if (entryID == 3) {
        carColor = entryID;
        printf("������ ������ => Blue\n");
    }
    else if (entryID == 2) {
        carColor = entryID;
        printf("������ ������ => Green\n");
    }
    else if (entryID == 1) {
        carColor = entryID;
        printf("������ ������ => Red\n");
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
    //initLight();
    srand((unsigned int)time(NULL));
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glutSpecialFunc(mySpecialKey);
    glutKeyboardFunc(myKey);
    glutTimerFunc(1000, myTimer, 0);
    MenuFunc();
    glutMainLoop();

    return 0;
}
