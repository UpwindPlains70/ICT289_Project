#ifndef COLLISIONDETECTIONAABB_H_INCLUDED
#define COLLISIONDETECTIONAABB_H_INCLUDED
#include <GL/freeglut.h>

#include "Geometry.h"
#include "player.h"
#include "Room.h"
#include "ball.h"
#include "globalTimer.h"


GLfloat maxYFloat; /// use this make sure player isn't halfway through the ground
GLfloat minYFloat;
int c = 0;
const int maxPlayerZ = 50; //Min = negative
const int minPlayerZ = 5; //Min = negative
const int minPlayerX = -60;
const int maxPlayerX = 20;

const int XcollisionBox = 10;
const int YcollisionBox = 10;
const int ZcollisionBox = 10;

const int maxFloorBounces = 2;
//bool hitFrontWall = false;

///Used by display callback function in main
void collisionPlayer(int i, ballObj *b){
        /// getting the position of the racket
        rackPos[i][0] = startingPos[i][0]  + playerArray[i].CoM[0];
        rackPos[i][1] = playerArray[i].CoM[1];
        rackPos[i][2] = startingPos[i][2] + playerArray[i].CoM[2];

        /// getting the vector between the racket and the ball
        b->vecRackToBall[0] = b->currPos[0] - rackPos[i][0];
        b->vecRackToBall[1] = b->currPos[1] - rackPos[i][1];
        b->vecRackToBall[2] = b->currPos[2] - rackPos[i][2];
    /// checking if collision has occurred by checking the vector between the ball and racket, and seeing if its within this collision box defined by X,Y and Z value for collisionBox
     if((b->vecRackToBall[0] <= XcollisionBox && b->vecRackToBall[0] >= -XcollisionBox) && (b->vecRackToBall[1] <= YcollisionBox && b->vecRackToBall[1] >= -YcollisionBox) && (b->vecRackToBall[2] <= ZcollisionBox && b->vecRackToBall[2] >= -ZcollisionBox)  ){
            b->hasHitBall[i] = true;
            resetFloorHitCount(b);

            hitBallForce(b->currVel, b->prevVel, i); /// function in physics to apply force
        }
}

void playerWallCollision(){
    //none of these make any sense until you see how they move
    for(int i = 0; i < maxPlayers; i++){
        //back
        if (playerArray[i].CoM[0] > maxPlayerX){
            playerArray[i].CoM[0] = maxPlayerX;
        }
        //front
        if (playerArray[i].CoM[0] < minPlayerX){
            playerArray[i].CoM[0] = minPlayerX;
        }
        //left
        if(i==0){
            if(playerArray[i].CoM[2] > minPlayerZ){
                playerArray[i].CoM[2] = minPlayerZ;
            }
        }else if(i==1){
            if(playerArray[i].CoM[2] > maxPlayerZ){
                playerArray[i].CoM[2] = maxPlayerZ;
            }
        }
        //right
        if(i==0){
            if(playerArray[i].CoM[2] < -maxPlayerZ){
                playerArray[i].CoM[2] = -maxPlayerZ;
            }
        }else if(i==1){
            if(playerArray[i].CoM[2] < -minPlayerZ){
                playerArray[i].CoM[2] = -minPlayerZ;
            }
        }
    }
}

void checkIfOutOfBounds(ballObj *b){

    if(b->currPos[1] >= frontWallLine[0][1] && b->hitFrontWall == true){
        scoreHandler(b);
    }else if(b->floorHitCount == maxFloorBounces){
        scoreHandler(b);
    }

    b->hitFrontWall = false;
}

void checkSideOutOfbounds(ballObj *b,float leftout, float rightout)
{
    if(leftout < ballArray[0].ballRadius){
        scoreHandler(b);
        //printf("L:::%f::%f\n",leftout,ballArray[0].ballRadius);
    }

    if(rightout < ballArray[0].ballRadius){
        scoreHandler(b);
        //printf("R:::%f::%f\n",rightout,ballArray[0].ballRadius);
    }
}

void scoreHandler(ballObj *b){

    if(b->whoseTurn[0] == true){
        /*if(b->hasHitBall[1] == true){
            increaseP1Score();
            b->hasHitBall[1] = false;
        }else{*/
            increaseP2Score();
            b->hasHitBall[0] = false;
        //}
    }
    else if(b->whoseTurn[1] == true){
        /*if(b->hasHitBall[0] == true){
            increaseP2Score();
            b->hasHitBall[0] = false;
        }else{*/
            increaseP1Score();
            b->hasHitBall[1] = false;
        //}
    }

    if(b->hitFrontWall == false)
        switchPlayerToHit(b);

        resetBall(b);
}

    //Change which player is meant to pass the ball
void switchPlayerToHit(ballObj *b){
    if(b->whoseTurn[0] == true){
        b->whoseTurn[0] = false;
        b->whoseTurn[1] = true;
    }else{
        b->whoseTurn[1] = false;
        b->whoseTurn[0] = true;
    }
}
#endif // COLLISIONDETECTIONAABB_H_INCLUDED
