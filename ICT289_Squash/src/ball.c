#include "../include/ball.h"

#include "../include/globals.h"
#include <stdio.h>
#include <stdlib.h>

inline void drawGameBall(ballObj *b){
    glColor3fv(b->ballColor);
    glTranslatef(b->currPos[0], b->currPos[1], b->currPos[2]);
    glutSolidSphere(b->ballRadius,15,15);
}

inline void resetBall(ballObj *b)
{
    b->ballRadius = 2.5;

    setBallVelocity(b);
    resetFloorHitCount(b);

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

    //Can be modifiead to be random values
    //For this project preset values are used (only one ball)
inline void setBallVelocity(ballObj *b){
    b->v0[0] = 100;
    b->v0[1] = 0;
    b->v0[2] = 0;
}

inline void resetFloorHitCount(ballObj *b){
    b->floorHitCount = 0;
}

inline void resetBallColor(ballObj *b)
{
    b->ballColor[0] = 0;
    b->ballColor[1] = 0;
    b->ballColor[2] = 0;
}

    ///Only applicable to single ball game
inline void writeWhoseTurn()
{
    if(ballArray[0].whoseTurn[0] == true)
        playerOneTurn();
    else if(ballArray[0].whoseTurn[1] == true)
        playerTwoTurn();
}
inline void playerOneTurn(){

  glColor3fv(textColor);
  sprintf (label, "Player One Pass");
  glRasterPos3i (5, 50,-5);
  drawString (label);
}

inline void playerTwoTurn(){

    glColor3fv(textColor);
    sprintf (label, "Player Two's Pass");
    glRasterPos3i (5, 50,-38);
    drawString (label);
}
