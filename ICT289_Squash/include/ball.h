#ifndef BALL_H
#define BALL_H

#include "globals.h"
#include "Geometry.h"

//ball initial position
const Point3D startPos = {20, 40, -20}; ///Serve pos for player One
const Point3D startPosB = {20, 40, -50}; ///Serve pos for player Two

    ///Allow for several balls to be created easily
typedef struct ballObj{
    float ballRadius;
    Point3D vecRackToBall;

    //current and previous position of ball
    Point3D currPos, prevPos;
    Point3D currVel, prevVel;

    //initial velocity for x,y,z directions
    Point3D v0; /// changing from 250

    Point3D ballColor;

    int floorHitCount;
    bool whoseTurn[2];
    bool hasHitBall[2];
    bool hitFrontWall;

}ballObj;

ballObj ballArray[1];//Only need one ball

    ///Position for text of whose turn it is in 3D world
const int plyr1PassDisp[] = {5, 50,-5};
const int plyr2PassDisp[] = {5, 50,-38};

void drawGameBall(ballObj *b){

    glColor3fv(b->ballColor);
    glTranslatef(b->currPos[0], b->currPos[1], b->currPos[2]);
    glutSolidSphere(b->ballRadius,15,15);
}

    ///Setup ball parameters
void resetBall(ballObj *b){

    b->ballRadius = 2.5;

    setBallVelocity(b);
        ///Need to reset floor count twice otherwise it may not work resulting in an instant point
    resetFloorHitCount(b);
    b->floorHitCount = 0;

        ///Player one always serves first
    if(gameStarted == false)
        b->whoseTurn[0] = true;

    if(b->whoseTurn[0] == true){
        b->currPos[0] = b->prevPos[0] = startPos[0];
        b->currPos[1] = b->prevPos[1] = startPos[1];
        b->currPos[2] = b->prevPos[2] = startPos[2];
    }else{
        b->currPos[0] = b->prevPos[0] = startPosB[0];
        b->currPos[1] = b->prevPos[1] = startPosB[1];
        b->currPos[2] = b->prevPos[2] = startPosB[2];
    }

    //velocity/s
    b->currVel[0] = b->prevVel[0] = b->v0[0];
    b->currVel[1] = b->prevVel[1] = b->v0[1];
    b->currVel[2] = b->prevVel[2] = b->v0[2];
}

    ///Can be modifiead to use random values
    ///For this project preset values are used (only one ball)
void setBallVelocity(ballObj *b){

    b->v0[0] = 100;
    b->v0[1] = 0;
    b->v0[2] = 0;
}

    ///Allows for other funtions to reset the count
void resetFloorHitCount(ballObj *b){

    b->floorHitCount = 0;
}

    ///Hard set ball color (only one ball)
    ///Could be modified to random values
void resetBallColor(ballObj *b){

    b->ballColor[0] = 0;
    b->ballColor[1] = 0;
    b->ballColor[2] = 0;
}

    ///Only applicable to single ball game
void writeWhoseTurn(){

    if(ballArray[0].whoseTurn[0] == true)
        playerOneTurn();
    else if(ballArray[0].whoseTurn[1] == true)
        playerTwoTurn();
}

void playerOneTurn(){

  glColor3fv(textColor);
  sprintf (label, "Player One Pass");
  glRasterPos3iv(plyr1PassDisp);
  drawString (label);
}

void playerTwoTurn(){

    glColor3fv(textColor);
    sprintf (label, "Player Two's Pass");
    glRasterPos3iv(plyr2PassDisp);
    drawString (label);
}
#endif //ball_H
