#ifndef PHYSICS_H
#define PHYSICS_H

#include "ball.h"
#include "player.h"
#include "collisionDetectionAABB.h"

typedef GLfloat point3[3];

//animation timers
float startTime, prevTime;
//size of ball *to calculate energy loss for "bouncy effect"
float ballRadius = 2.5;
//level of energy loss
float dropOff = 0.75;
// gravity (earth) (affects velocity)
point3 g = {0, -980, 0};
//ball initial position
Point3D startPos = {0, 50, -23}; /// changed from 150 y
//current and previous position of ball
point3 currPos, prevPos;
//initial velocity for x,y,z directions
point3 v0 ={100, 0, 0}; /// changing from 250 x
//current and previous velocity
point3 currVel, prevVel;

BOOL hitBackWall = FALSE;

max maP1,maP2;
min miP1,miP2;

//animation
void animate(void)
{
    //find magnitude of radius vector
    glutTimerFunc(TIMER, animate, 0);
    float currTime;
    float timePrevCur;
    float collision;

    currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0 ;
    timePrevCur = currTime - prevTime;

    //"fall"
    currPos[0] = prevPos[0] + (prevVel[0] * timePrevCur) + (g[0] * timePrevCur * timePrevCur / 2);
    currPos[1] = prevPos[1] + (prevVel[1] * timePrevCur) + (g[1] * timePrevCur * timePrevCur / 2);
    currPos[2] = prevPos[2] + (prevVel[2] * timePrevCur) + (g[2] * timePrevCur * timePrevCur / 2);

    //find velocity
    currVel[0] = prevVel[0] + (g[0] * timePrevCur);
    currVel[1] = prevVel[1] + (g[1] * timePrevCur);
    currVel[2] = prevVel[2] + (g[2] * timePrevCur);

    //energy drop off when collision occurs
    //floor collision
    if (currPos[1] <= ballRadius){
        currVel[1] = -currVel[1] * dropOff;
        currPos[1] = ballRadius;
    }

    ////wall collisions
    //back
    if (currPos[0] >= (54.4 + 16.0 + 26.1)){
        currVel[0] = -currVel[0];
    }
    //front *for some reason ball spawns before x0 position even when specified 0, somehow spawns before till it reaches >-20x
    if (currPos[0] <= 0.0){
        currPos[0] = 0.0;
        currVel[0] = -currVel[0];
        hitBackWall = TRUE;
    }
    else{
        hitBackWall = FALSE;
    }
    //left
    if (currPos[2] >= 0 ){
        currVel[2] = -currVel[2];
    }
    //right
    if (currPos[2] <= -64 ){
        currVel[2] = -currVel[2];
    }

    //racket collision
    racketCollision(currPos);


    ////make current position previous for next loop
    //position
    prevPos[0] = currPos[0];
    prevPos[1] = currPos[1];
    prevPos[2] = currPos[2];
    //velocity
    prevVel[0] = currVel[0];
    prevVel[1] = currVel[1];
    prevVel[2] = currVel[2];
    //time
    prevTime = currTime;

    glutPostRedisplay();
}

void initPositions(){
    currPos[0] = startPos[0];
    currPos[1] = startPos[1];
    currPos[2] = startPos[2];
    prevPos[0] = startPos[0];
    prevPos[1] = startPos[1];
    prevPos[2] = startPos[2];
    //velocity/s
    prevVel[0] = v0[0];
    prevVel[1] = v0[1];
    prevVel[2] = v0[2];
    currVel[0] = v0[0];
    currVel[1] = v0[1];
    currVel[2] = v0[2];
}

#endif //physics_H
