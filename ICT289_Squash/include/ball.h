#ifndef BALL_H
#define BALL_H

//#include "physics.h"



BOOL hasHitBall[2] = {FALSE, FALSE};
//ball initial position
const Point3D startPos = {0, 50, -23}; /// changed from 150 y
//current and previous position of ball





typedef struct ballObj{


    float ballRadius;

    Point3D vecRackToBall;

    Point3D currPos, prevPos;
    Point3D currVel, prevVel;

    Point3D ballColor;



}ballObj;

ballObj ballArray[1];


//size of ball *to calculate energy loss for "bouncy effect"

//float ballRadius = 2.5;
//current and previous velocity



void drawGameBall(ballObj *b)
{
    glColor3fv(b->ballColor);
    glTranslatef(b->currPos[0], b->currPos[1], b->currPos[2]);
    glutSolidSphere(b->ballRadius,15,15);
}

void resetBall(ballObj *b)
{
    b->ballRadius = 2.5;


    b->ballColor[0] = 0;
    b->ballColor[1] = 0;
    b->ballColor[2] = 0;

    b->currPos[0] = b->prevPos[0] = startPos[0];
    b->currPos[1] = b->prevPos[1] = startPos[1];
    b->currPos[2] = b->prevPos[2] = startPos[2];
}

#endif //ball_H
