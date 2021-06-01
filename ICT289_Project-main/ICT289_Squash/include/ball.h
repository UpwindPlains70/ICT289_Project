#ifndef BALL_H
#define BALL_H

//#include "physics.h"

Point3D ballColor = {0,0,0};

BOOL hasHitBall[2] = {FALSE, FALSE};
//ball initial position
Point3D startPos = {0, 50, -23}; /// changed from 150 y
//current and previous position of ball
Point3D currPos, prevPos;
Point3D vecRackToBall;

//size of ball *to calculate energy loss for "bouncy effect"
float ballRadius = 2.5;
void drawGameBall()
{
    glColor3fv(ballColor);
    glTranslatef(currPos[0], currPos[1], currPos[2]);
    glutSolidSphere(ballRadius,5,5);
}

void resetBall()
{
    ballColor[0] = 0;
    ballColor[1] = 0;
    ballColor[2] = 0;

    currPos[0] = prevPos[0] = startPos[0];
    currPos[1] = prevPos[1] = startPos[1];
    currPos[2] = prevPos[2] = startPos[2];
}

#endif //ball_H
