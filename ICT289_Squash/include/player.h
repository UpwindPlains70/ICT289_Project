#ifndef PLAYER_H
#define PLAYER_H

#ifdef _WIN32
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif

#include "Geometry.h"
#include "globals.h"

#define maxPlayers 2
typedef enum {reset, hit, idle, powering, cooling} swingStates; ///animation control states for character swing

typedef struct playerObj{
    Object3D charObj;
    Point3D CoM;
    Point3D startPos;

    Object3D handle;
    Object3D pad;
    Point3D handleCoM;
    Point3D padCoM;

    float currSwingAngle;
    swingStates swingMode;
    int powerLevel;
}playerObj;


//float startTime, prevTime;
//float currTime;
//float timeSincePrevFrame;

const float maxSpeedMod = 150; ///Allows for adjustable player speed
const float minSpeedMod = 80;
const float defaultSpeedMod = 100;

float speedMod = 100; /// control the speed of all the movements

typedef GLdouble Colours[3];
const Colours playerColours[2] = {{0.0, 0.0, 1.0},{0.0, 1.0, 0.0}};

playerObj playerArray[maxPlayers];
const Point3D startingPos[2] = { {70.0, 0.0, -10.0}, {70.0, 0.0, -55.0}  };   // 77.0, 0, -15.0); /// starting location of player1  // (77.0, 0 , -50.0); /// starting location of player2
Point3D rackPos[2];
const int maxPowerLevel = 10;

    ///Swing animation parameters
//#define TIMERMSECS 150 /// callback frequency
const int maxSwingAngle = 60; ///Max swing angle of players

const float maxSwingSpeed = 220; ///Allows for adjustable game parameters
const float minSwingSpeed = 180;
const float defaultSwingSpeed = 200;

float swingSpeed = 200; ///speed of swing & reset

const float playerScale[] = {0.02,0.02,0.02};
const float handleColor[] = {0.6, 0.2, 0.2};
const float padColor[] = {0.7,0.7,0.7};

const float increaseRate = 1.0;
const float decreaseRate = 1.0;

const float plyr2PowerBL[] = {5,8,-57};
const float plyr2PowerTL[] = {5,8,-52};
const float plyr2PowerTR[] = {5,13,-52};
const float plyr2PowerBR[] = {5,13,-57};

const float plyr1PowerBL[] = {5,8,-5};
const float plyr1PowerTL[] = {5,8,-10};
const float plyr1PowerTR[] = {5,13,-10};
const float plyr1PowerBR[] = {5,13,-5};

void drawPlayer(int i, GLdouble colour[]){
//Draw player (Capsule)

    glColor3f(colour[0], colour[1], colour[2]);   // 0.4, 0.1, 0.1
    glScalef(playerScale[0], playerScale[1], playerScale[2]);
    draw3DObject(playerArray[i].charObj);

}

    //Draw racket
void drawRacket(int i){

    glColor3fv(handleColor);
    draw3DObject(playerArray[i].handle);
    glColor3fv(padColor);
    draw3DObject(playerArray[i].pad);

}

    //Cannot be reused as animation functions can only have void parameter
void playerOneSwing(void){

    if(playerArray[0].swingMode != idle)
        glutTimerFunc(TIMERMSECSA, playerOneSwing, 0);

    //Get elapsed time in seconds
    float currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    float timeSincePrevFrame = currTime - prevTime;

    //Update days

        ///First check for reset otherwise if not idle swing
    if((playerArray[0].currSwingAngle >= maxSwingAngle) || ((playerArray[0].swingMode == reset) && (playerArray[0].swingMode != idle)))
    {
        playerArray[0].swingMode = reset;
        playerArray[0].currSwingAngle -= swingSpeed * timeSincePrevFrame * playerArray[0].powerLevel;
    }
    else if(playerArray[0].swingMode != idle)
    {
         playerArray[0].currSwingAngle += swingSpeed * timeSincePrevFrame * playerArray[0].powerLevel;
    }

        ///Set swing mode to idle as animation has completed
    if(playerArray[0].currSwingAngle < 0 && playerArray[0].swingMode == reset)
    {
        playerArray[0].swingMode = idle;
        playerArray[0].powerLevel = 1;
    }

    //save current time for use in next frame
    prevTime = currTime;

    glutPostRedisplay();
}

    //Cannot be reused as animation functions can only have void parameter
void playerTwoSwing(void){

    if(playerArray[1].swingMode != idle)
        glutTimerFunc(TIMERMSECSB, playerTwoSwing, 0);

    //Get elapsed time in seconds
    float currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    float timeSincePrevFrame = currTime - prevTime;

    //Update days

        ///First check for reset otherwise if not idle swing
    if(playerArray[1].currSwingAngle >= maxSwingAngle || playerArray[1].swingMode == reset && playerArray[1].swingMode != idle)
    {
        playerArray[1].swingMode = reset;
        playerArray[1].currSwingAngle -= swingSpeed * timeSincePrevFrame * playerArray[1].powerLevel;
    }
    else if(playerArray[1].swingMode != idle)
    {
         playerArray[1].currSwingAngle += swingSpeed * timeSincePrevFrame * playerArray[1].powerLevel;
    }

        ///Set swing mode to idle as animation has completed
    if(playerArray[1].currSwingAngle < 0 && playerArray[1].swingMode == reset)
    {
        playerArray[1].swingMode = idle;
        playerArray[1].powerLevel = 1;
    }

    //save current time for use in next frame
    prevTime = currTime;

    glutPostRedisplay();
}

void powerLevelHandler(playerObj *player){
    if(player->swingMode != cooling || player->powerLevel == 1)
            player->swingMode = powering;

    if(player->powerLevel < maxPowerLevel && player->swingMode != cooling)
        player->powerLevel++;
    else{
        player->powerLevel--;
        player->swingMode = cooling;
    }
}

void drawPlayerTwoPower(){

    glColor3f(0+playerArray[1].powerLevel/10.0,1-playerArray[1].powerLevel/10.0,0);
    glBegin(GL_POLYGON);
        glVertex3fv(plyr2PowerBL);
        glVertex3fv(plyr2PowerTL);
        glVertex3fv(plyr2PowerTR);
        glVertex3fv(plyr2PowerBR);
    glEnd();
}

void drawPlayerOnePower(){

    glColor3f(0+playerArray[0].powerLevel/10.0,1-playerArray[0].powerLevel/10.0,0);
    glBegin(GL_POLYGON);
        glVertex3fv(plyr1PowerBL);
        glVertex3fv(plyr1PowerTL);
        glVertex3fv(plyr1PowerTR);
        glVertex3fv(plyr1PowerBR);
    glEnd();
}

void increasePlayerSpeed(){

    if(speedMod < maxSpeedMod)
        speedMod++; ///Increase speed by one
    else
        printf("Player speed is at maximum: %f\n", speedMod);
}

void decreasePlayerSpeed(){

    if(speedMod > minSpeedMod)
        speedMod--; ///Increase speed by one
    else
        printf("Player speed is at minimum: %f\n", speedMod);
}

void increaseSwingSpeed(){

    if(swingSpeed < maxSwingSpeed)
        swingSpeed += increaseRate;
    else
        printf("Swing speed is at maximum: %f\n", swingSpeed);
}

void decreaseSwingSpeed(){

    if(swingSpeed > minSwingSpeed)
        swingSpeed -= decreaseRate;
    else
        printf("Swing speed is at minimum: %f\n", swingSpeed);
}

void resetPlayerPos(){

    for(int i = 0; i < maxPlayers; i++){
        playerArray[i].CoM[0] = playerArray[i].startPos[0];

        playerArray[i].CoM[2] = playerArray[i].startPos[2];
    }
}

#endif // PLAYER_H
