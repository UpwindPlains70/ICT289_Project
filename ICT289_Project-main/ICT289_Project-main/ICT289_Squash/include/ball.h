#ifndef BALL_H
#define BALL_H

#include "physics.h"

Point3D ballColor = {0,0,0};

void drawGameBall()
{
    glColor3fv(ballColor);
    glTranslatef(currPos[0], currPos[1], currPos[2]);
    glutSolidSphere(ballRadius,5,5);
}

void changeBallColor()
{
    ballColor[0] += 0.01;
}

void resetBall()
{
    ballColor[0] = 0;
    ballColor[1] = 0;
    ballColor[2] = 0;

    currPos[0] = prevPos[0] = startPos[0];
    currPos[1] = prevPos[0] = startPos[1];
    currPos[2] = prevPos[0] = startPos[2];
}

#endif //ball_H
