#pragma warning (disable:4996)

#include <windows.h>
#include <glut.h> 
#include <glu.h>
#include <gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <Digitalv.h>


// Sound
#define BACKGROUND "BGM\\background.wav"

GLfloat light0Position[] = { 0, 8, 3, 1.0 };
GLfloat light1Position[] = { 0, 8, 3, 1.0 };

// gameStatus, frame, gameScore, carSpeed
int isGaming = 0, FPS = 50, score = 0, speed = 1;

// Map
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;

// Car x index
int lrIndex = 0;

// Coming Cars index
int comingCar1 = 0;
int cCar1Index = 0;
int comingCar2 = 35;
int cCar2Index = 0;
int comingCar3 = 70;
int cCar3Index = 0;
int randomCar1;

// User Life
GLfloat life1 = 1, life2 = 1, life3 = 1;
int lifeIndex = 80;

int carColor;

// Material Color, feature
const GLfloat white[] = { 1.0, 1.0, 1.0, 0.2 };
const GLfloat black[] = { 0.5, 0.5, 0.5, 0.2 };
const GLfloat polished[] = { 100.0 };

// Coin&Booster x,y index
int coin1 = 0, coin2 = 10, coin3 = 20, coin4 = 30, coin5 = 40;
int coinIdx1 = 0, coinIdx2 = 0, coinIdx3 = 0, coinIdx4 = 0, coinIdx5 = 0;
int booster = 0, boosterIdx = 0;
// probability of creating coin item
int randomcoin = 0;
// probability of creating booster item, booster duration, check getting booster
int createBoost = 0, randomBooster, duration = 0, isBoosting = 0;

// Text Font
void* font1 = GLUT_BITMAP_TIMES_ROMAN_24;
void* font2 = GLUT_BITMAP_HELVETICA_18;
void* font3 = GLUT_BITMAP_8_BY_13;
// Save Score Buffer
char buffer1[50], buffer2[50];
// Play Time
int play = 0;
// Save Name & Score
char* player[10][10];
int record[10];
// Print text on screen
void renderBitmapString(float x, float y, void* font, const char* string)
{
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}
// Save Score
void Record() {
    printf("이름을 입력해주세요.예)AAA, BBB, ABC\n이름 : ");
    scanf("%s", (const char*)player[play]);
    record[play] = score;
    play++;
    glColor3f(1.0, 1.0, 1.0);
}
//game screen
void startGame()
{
    glEnable(GL_LIGHTING);
    //Road
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glMaterialfv(GL_FRONT, GL_SHININESS, polished);

    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();

    //Border
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, polished);
    //Road Middel Border
    //Top
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivTop + 80);
    glVertex2f(48, roadDivTop + 100);
    glVertex2f(52, roadDivTop + 100);
    glVertex2f(52, roadDivTop + 80);
    glEnd();
    roadDivTop -= speed;
    if (roadDivTop < -100) {
        roadDivTop = 20;
        if (speed == 1)
            score++;
        else
            score += 3;
    }
    //Middle
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivMdl + 40);
    glVertex2f(48, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 40);
    glEnd();
    roadDivMdl -= speed;
    if (roadDivMdl < -60) {
        roadDivMdl = 60;
        if (speed == 1)
            score++;
        else
            score += 3;
    }
    //Bottom
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivBtm + 0);
    glVertex2f(48, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm + 0);
    glEnd();
    roadDivBtm -= speed;
    if (roadDivBtm < -20) {
        roadDivBtm = 100;
        if (speed == 1)
            score++;
        else
            score += 3;
    }

    //Road Left Border
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(23, 100);
    glVertex2f(23, 0);
    glEnd();

    //Road Right Border
    glBegin(GL_POLYGON);
    glVertex2f(77, 0);
    glVertex2f(77, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();
    glDisable(GL_LIGHTING);


    // Score board
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

    // User life Status
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

    // Probability of creating coin
    randomcoin = rand() % 40;

    // Coin1(increasing score)
     glColor3f(1.0, 1.0, 0.0);
glBegin(GL_POLYGON);
glVertex2f(coinIdx1 + 27, coin1 + 97);
glVertex2f(coinIdx1 + 29, coin1 + 97);
glVertex2f(coinIdx1 + 30, coin1 + 96);
glVertex2f(coinIdx1 + 30, coin1 + 95);
glVertex2f(coinIdx1 + 29, coin1 + 94);
glVertex2f(coinIdx1 + 27, coin1 + 94);
glVertex2f(coinIdx1 + 26, coin1 + 95);
glVertex2f(coinIdx1 + 26, coin1 + 96);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(coinIdx1 + 26.5, coin1 + 95);
glVertex2f(coinIdx1 + 26.5, coin1 + 96);
glVertex2f(coinIdx1 + 27.25, coin1 + 96.75);
glVertex2f(coinIdx1 + 29, coin1 + 96.75);
glVertex2f(coinIdx1 + 29, coin1 + 96.25);
glVertex2f(coinIdx1 + 27.25, coin1 + 96.25);
glVertex2f(coinIdx1 + 26.5, coin1 + 95);
glVertex2f(coinIdx1 + 29, coin1 + 95);
glVertex2f(coinIdx1 + 29, coin1 + 94.5);
glVertex2f(coinIdx1 + 26.5, coin1 + 94.5);
glEnd();
    // Move coin
    if (coin1 > -100)
        coin1 -= speed;
    // Check getting coin
    if ((abs(lrIndex - coinIdx1) < 4) && ((coin1 + 100) > 6) && ((coin1 + 100) < 17)) {
        score += 3;
        coin1 = -100;
    }
    // Recreate coin
    if (coin1 <= -100 && randomcoin == 1)
    {
        coinIdx1 = rand() % 50;
        coin1 = rand() % 10;
    }

    // Coin2
     glColor3f(1.0, 1.0, 0.0);
glBegin(GL_POLYGON);
glVertex2f(coinIdx2 + 27, coin2 + 97);
glVertex2f(coinIdx2 + 29, coin2 + 97);
glVertex2f(coinIdx2 + 30, coin2 + 96);
glVertex2f(coinIdx2 + 30, coin2 + 95);
glVertex2f(coinIdx2 + 29, coin2 + 94);
glVertex2f(coinIdx2 + 27, coin2 + 94);
glVertex2f(coinIdx2 + 26, coin2 + 95);
glVertex2f(coinIdx2 + 26, coin2 + 96);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(coinIdx2 + 26.5, coin2 + 95);
glVertex2f(coinIdx2 + 26.5, coin2 + 96);
glVertex2f(coinIdx2 + 27.25, coin2 + 96.75);
glVertex2f(coinIdx2 + 29, coin2 + 96.75);
glVertex2f(coinIdx2 + 29, coin2 + 96.25);
glVertex2f(coinIdx2 + 27.25, coin2 + 96.25);
glVertex2f(coinIdx2 + 26.5, coin2 + 95);
glVertex2f(coinIdx2 + 29, coin2 + 95);
glVertex2f(coinIdx2 + 29, coin2 + 94.5);
glVertex2f(coinIdx2 + 26.5, coin2 + 94.5);
glEnd();
    if (coin2 > -100)
        coin2 -= speed;

    if ((abs(lrIndex - coinIdx2) < 4) && ((coin2 + 100) > 6) && ((coin2 + 100) < 17)) {
        score += 3;
        coin2 = -100;
    }

    if (coin2 <= -100 && randomcoin == 1)
    {
        coinIdx2 = rand() % 50;
        coin2 = rand() % 10;
    }
    // Coin3
    glColor3f(1.0, 1.0, 0.0);
glBegin(GL_POLYGON);
glVertex2f(coinIdx3 + 27, coin3 + 97);
glVertex2f(coinIdx3 + 29, coin3 + 97);
glVertex2f(coinIdx3 + 30, coin3 + 96);
glVertex2f(coinIdx3 + 30, coin3 + 95);
glVertex2f(coinIdx3 + 29, coin3 + 94);
glVertex2f(coinIdx3 + 27, coin3 + 94);
glVertex2f(coinIdx3 + 26, coin3 + 95);
glVertex2f(coinIdx3 + 26, coin3 + 96);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(coinIdx3 + 26.5, coin3 + 95);
glVertex2f(coinIdx3 + 26.5, coin3 + 96);
glVertex2f(coinIdx3 + 27.25, coin3 + 96.75);
glVertex2f(coinIdx3 + 29, coin3 + 96.75);
glVertex2f(coinIdx3 + 29, coin3 + 96.25);
glVertex2f(coinIdx3 + 27.25, coin3 + 96.25);
glVertex2f(coinIdx3 + 26.5, coin3 + 95);
glVertex2f(coinIdx3 + 29, coin3 + 95);
glVertex2f(coinIdx3 + 29, coin3 + 94.5);
glVertex2f(coinIdx3 + 26.5, coin3 + 94.5);
glEnd();
    if (coin3 > -100)
        coin3 -= speed;

    if ((abs(lrIndex - coinIdx3) < 4) && ((coin3 + 100) > 6) && ((coin3 + 100) < 17)) {
        score += 3;
        coin3 = -100;
    }

    if (coin3 <= -100 && randomcoin == 1)
    {
        coinIdx3 = rand() % 50;
        coin3 = rand() % 10;
    }
    // Coin4
    glColor3f(1.0, 1.0, 0.0);
glBegin(GL_POLYGON);
glVertex2f(coinIdx4 + 27, coin4 + 97);
glVertex2f(coinIdx4 + 29, coin4 + 97);
glVertex2f(coinIdx4 + 30, coin4 + 96);
glVertex2f(coinIdx4 + 30, coin4 + 95);
glVertex2f(coinIdx4 + 29, coin4 + 94);
glVertex2f(coinIdx4 + 27, coin4 + 94);
glVertex2f(coinIdx4 + 26, coin4 + 95);
glVertex2f(coinIdx4 + 26, coin4 + 96);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(coinIdx4 + 26.5, coin4 + 95);
glVertex2f(coinIdx4 + 26.5, coin4 + 96);
glVertex2f(coinIdx4 + 27.25, coin4 + 96.75);
glVertex2f(coinIdx4 + 29, coin4 + 96.75);
glVertex2f(coinIdx4 + 29, coin4 + 96.25);
glVertex2f(coinIdx4 + 27.25, coin4 + 96.25);
glVertex2f(coinIdx4 + 26.5, coin4 + 95);
glVertex2f(coinIdx4 + 29, coin4 + 95);
glVertex2f(coinIdx4 + 29, coin4 + 94.5);
glVertex2f(coinIdx4 + 26.5, coin4 + 94.5);
glEnd();
    if (coin4 > -100)
        coin4 -= speed;

    if ((abs(lrIndex - coinIdx4) < 4) && ((coin4 + 100) > 6) && ((coin4 + 100) < 17)) {
        score += 3;
        coin4 = -100;
    }

    if (coin4 <= -100 && randomcoin == 1)
    {
        coinIdx4 = rand() % 50;
        coin4 = rand() % 10;
    }
    // Coin5
     glColor3f(1.0, 1.0, 0.0);
glBegin(GL_POLYGON);
glVertex2f(coinIdx5 + 27, coin5 + 97);
glVertex2f(coinIdx5 + 29, coin5 + 97);
glVertex2f(coinIdx5 + 30, coin5 + 96);
glVertex2f(coinIdx5 + 30, coin5 + 95);
glVertex2f(coinIdx5 + 29, coin5 + 94);
glVertex2f(coinIdx5 + 27, coin5 + 94);
glVertex2f(coinIdx5 + 26, coin5 + 95);
glVertex2f(coinIdx5 + 26, coin5 + 96);
glEnd();

glColor3f(0.0, 0.0, 0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(coinIdx5 + 26.5, coin5 + 95);
glVertex2f(coinIdx5 + 26.5, coin5 + 96);
glVertex2f(coinIdx5 + 27.25, coin5 + 96.75);
glVertex2f(coinIdx5 + 29, coin5 + 96.75);
glVertex2f(coinIdx5 + 29, coin5 + 96.25);
glVertex2f(coinIdx5 + 27.25, coin5 + 96.25);
glVertex2f(coinIdx5 + 26.5, coin5 + 95);
glVertex2f(coinIdx5 + 29, coin5 + 95);
glVertex2f(coinIdx5 + 29, coin5 + 94.5);
glVertex2f(coinIdx5 + 26.5, coin5 + 94.5);
glEnd();
    glEnd();
    if (coin5 > -100)
        coin5 -= speed;

    if ((abs(lrIndex - coinIdx5) < 4) && ((coin5 + 100) > 6) && ((coin5 + 100) < 17)) {
        score += 3;
        coin5 = -100;
    }

    if (coin5 <= -100 && randomcoin == 1)
    {
        coinIdx5 = rand() % 50;
        coin5 = rand() % 10;
    }

    // Booster
    // Probability of creating booster
    if (createBoost == 0)
    {
        randomBooster = rand() % 20;
    }
    // Create Booster
    if (randomBooster == 1)
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

        //Check getting booster
        if ((abs(lrIndex - boosterIdx) < 4) && ((booster + 100) > 5) && ((booster + 100) < 16)) {
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
    // Coming car1
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
    // Move coming car
    if (speed == 1)
        comingCar1--;
    else
        comingCar1 -= speed;
    // Recreate coming car
    if (comingCar1 < -100) {
        comingCar1 = 0;
        cCar1Index = rand() % 45;
    }
    // Check crashing with coming car
    if ((abs(lrIndex - cCar1Index) < 8) && (comingCar1 + 100 < 16)) {
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
        comingCar1 = 0;
        cCar1Index = rand() % 45;
    }


    // Coming car2
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
    if ((abs(lrIndex - cCar2Index) < 8) && (comingCar2 + 100 < 16)) {
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
        comingCar2 = 0;
        cCar2Index = rand() % 45;
    }
    // Coming car3
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
    if ((abs(lrIndex - cCar3Index) < 8) && (comingCar3 + 100 < 16)) {
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
        comingCar3 = 0;
        cCar3Index = rand() % 45;
    }

    //User car
    //headLight   
    glPushMatrix();
    glTranslatef(lrIndex + 27, 9, 3);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    glDisable(GL_LIGHT0);
    glColor3f(0.9, 0.9, 0.9);
    glutSolidSphere(1, 40, 40);
    glEnable(GL_LIGHT0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(lrIndex + 29, 9, 3);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
    glDisable(GL_LIGHT1);
    glColor3d(0.9, 0.9, 0.9);
    glutSolidSphere(1, 40, 40);
    glEnable(GL_LIGHT1);
    glPopMatrix();
    // Front Tire
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
    // GameOver screen
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
        sprintf(buffer2, "%d", score);
        renderBitmapString(15, 60, (void*)font2, "Score : ");
        renderBitmapString(28, 60, (void*)font2, buffer2);
        glColor3f(0.0f, 0.0f, 0.0f);
        renderBitmapString(15, 50, (void*)font2, "If you want to restart game Press space bar");
        glColor3f(1.0f, 1.0f, 1.0f);
        renderBitmapString(40, 85, (void*)font2, "The racer");


        glColor3f(0.0f, 1.0f, 0.0f);
        renderBitmapString(30, 30, (void*)font2, "Press SPACE to START");

        glColor3f(1.0f, 1.0f, 1.0f);
        renderBitmapString(30, 24, (void*)font3, "Press RIGHT to turn Right");
        renderBitmapString(30, 22, (void*)font3, "Press LEFT to turn Left");
        renderBitmapString(30, 20, font3, "Press S to save your score");
        renderBitmapString(30, 18, font3, "Press B to move start menu");
    }
    // Score Board Screen
    else if (isGaming == 3)
    {
        glColor3f(1.0, 1.0, 1.0);
        if (play == 0)
        {
            renderBitmapString(25, 50 + 10, font2, "No Record");
            renderBitmapString(25, 50 + 10 - 3, font2, "Press B to move start menu");
        }
        else if (play != 0) {
            for (int i = 0; i < play; i++)
            {
                renderBitmapString(30, 95 - (i * 2), font3, (const char*)player[i]);
                sprintf(buffer2, "%d", record[i]);
                renderBitmapString(60, 95 - (i * 2), font3, buffer2);
            }
            renderBitmapString(25, 30, font2, "Press B to move start menu");
        }
    }
    // Start Screen
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
        renderBitmapString(40, 80, font1, "The racer");

        glColor3f(0.0f, 1.0f, 0.0f);
        renderBitmapString(30, 60, font2, "Press SPACE to START");

        glColor3f(1.0f, 1.0f, 1.0f);
        renderBitmapString(27, 52, font3, "Press RIGHT to turn Right");
        renderBitmapString(27, 50, font3, "Press LEFT to turn Left");
        renderBitmapString(27, 48, font3, "Press S to move ScoreBoard");
        renderBitmapString(27, 46, font3, "Click Right Button to Change Color");
    }
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // move to game screen
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
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glOrtho(0, 100, 0, 100, -5, 5);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}
// Change frame every second
void myTimer(int value)
{
    duration++;
    // Booster duration
    if (duration == 250)
    {
        speed = 1;
        duration = 0;
    }
    // If you get booster
    if (isBoosting == 1)
    {
        isBoosting = 0;
        duration = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, myTimer, 0);
}
// Manipulate car
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
// Sub function(Start game, move to score board)
void myKey(unsigned char key, int x, int y)
{
    if (isGaming == 0)
    {
        if (key == 32)
        {
            PlaySound(TEXT(BACKGROUND), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            duration = 0, isBoosting = 0;
            score = 0, speed = 1, createBoost = 0;

            lrIndex = 0;

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
        else if (key == 's')
        {
            isGaming = 3;
        }
    }
    else if (isGaming == 2)
    {
        if (key == 32)
        {
            duration = 0, isBoosting = 0;
            score = 0, speed = 1, createBoost = 0;

            lrIndex = 0;

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
        else if (key == 's')
        {
            Record();
        }
        else if (key == 'b')
        {
            isGaming = 0;
        }
    }
    else if (isGaming == 3)
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
    GLfloat light0Ambient[] = { 1, 1, 1, 0.2 };
    GLfloat light0Diffuse[] = { 1, 1, 1, 1.0 };
    GLfloat light0Specular[] = { 1.0, 1.0, 1.0, 1 };
    GLfloat light0Cutoff[] = { 80 };
    GLfloat materialAmbient[] = { 1, 1, 1, 0.2 };
    GLfloat materialDiffuse[] = { 1, 1, 1, 1.0 };
    GLfloat materialSpecular[] = { 1.0, 1.0, 1.0, 1 };
    GLfloat materialShininess[] = { 80 };

    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, light0Cutoff);

    GLfloat light1Ambient[] = { 1, 1, 1, 0.2 };
    GLfloat light1Diffuse[] = { 1, 1, 1, 1.0 };
    GLfloat light1Specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light1Cutoff[] = { 80 };

    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, light1Cutoff);
}
// Select car color
void MenuProc(int entryID) {
    if (entryID == 3) {
        carColor = entryID;
        printf("Car Color => Blue\n");
    }
    else if (entryID == 2) {
        carColor = entryID;
        printf("Car Color => Green\n");
    }
    else if (entryID == 1) {
        carColor = entryID;
        printf("Car Color => Red\n");
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

    init(); initLight();
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