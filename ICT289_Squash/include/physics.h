#ifndef PHYSICS_H
#define PHYSICS_H

#include "ball.h"
#include "player.h"
#include "collisionDetectionAABB.h"

//level of energy loss
float dropOff = 0.3;
const float defaultDropOff = 0.3;
const float maxDropOff = 0.75;
const float minDropOff = 0.20;
const float dropOffIncreaseRate = 0.05;

const float colorChangeRate = 0.2;

float distToLeftOut;
float distToRightOut;
// gravity (earth) (affects velocity)
Point3D g = {0, -980, 0};

const float hitSpeedX = 20.0;
const float hitSpeedY = 15.0;
const float hitSpeedZ = 1.2;

const float bounceIncreaseRate = 0.1;
const float bounceDecreaseRate = 0.1;

//animation
void physics(void){

    //find magnitude of radius vector
    if(gameStarted == true)
        glutTimerFunc(TIMER, physics, 0);

    calcTimeSinceLastFrame();

    //"fall"
    ballArray[0].currPos[0] = ballArray[0].prevPos[0] + (ballArray[0].prevVel[0] * timeSincePrevFrame) + (g[0] * timeSincePrevFrame * timeSincePrevFrame / 2);
    ballArray[0].currPos[1] = ballArray[0].prevPos[1] + (ballArray[0].prevVel[1] * timeSincePrevFrame) + (g[1] * timeSincePrevFrame * timeSincePrevFrame / 2);
    ballArray[0].currPos[2] = ballArray[0].prevPos[2] + (ballArray[0].prevVel[2] * timeSincePrevFrame) + (g[2] * timeSincePrevFrame * timeSincePrevFrame / 2);

    //find velocity
    ballArray[0].currVel[0] = ballArray[0].prevVel[0] + (g[0] * timeSincePrevFrame);
    ballArray[0].currVel[1] = ballArray[0].prevVel[1] + (g[1] * timeSincePrevFrame);
    ballArray[0].currVel[2] = ballArray[0].prevVel[2] + (g[2] * timeSincePrevFrame);

    //energy drop off when collision occurs
    //floor collision
    if (ballArray[0].currPos[1] <= ballArray[0].ballRadius){
        ballArray[0].currVel[1] = -ballArray[0].currVel[1] * dropOff;
        ballArray[0].currPos[1] = ballArray[0].ballRadius;

        ballArray[0].floorHitCount++;

        checkIfOutOfBounds(&ballArray[0]);
    }

    ////wall collisions
    //back
    if (ballArray[0].currPos[0] >= gamefloor[2][0]){
        ballArray[0].currVel[0] = -ballArray[0].currVel[0];

        resetFloorHitCount(&ballArray[0]);
    }

    //front (Wall with score)
    if (ballArray[0].currPos[0] <= gamefloor[0][0]){

        resetFloorHitCount(&ballArray[0]);
        ballArray[0].currPos[0] += ballArray[0].ballRadius;
        ballArray[0].currVel[0] = -ballArray[0].currVel[0] * dropOff;
        ballArray[0].currVel[1] = -ballArray[0].currVel[1];
        ballArray[0].hitFrontWall = TRUE;

        checkIfOutOfBounds(&ballArray[0]);
        switchPlayerToHit(&ballArray[0]);
        changeBallColor(&ballArray[0]);

    }

   //left
    if (ballArray[0].currPos[2] >= gamefloor[0][0] - ballArray[0].ballRadius){

        resetFloorHitCount(&ballArray[0]);
        distToLeftOut = distanceFromSphereToPlane(ballArray[0].currPos, leftSideWallLine[0], leftSideWallLine[1], leftWall[1]-10);

        if(distToLeftOut < ballArray[0].ballRadius){
            scoreHandler(&ballArray[0]);
        //printf("L:::%f::%f\n",leftout,ballArray[0].ballRadius);
        }else{
            ballArray[0].currVel[2] = -ballArray[0].currVel[2] * dropOff;
            ballArray[0].currPos[2] -= ballArray[0].ballRadius;
        }
    }

    //right
    if (ballArray[0].currPos[2] <= gamefloor[1][2] + ballArray[0].ballRadius){

        resetFloorHitCount(&ballArray[0]);
        distToRightOut = distanceFromSphereToPlane(ballArray[0].currPos, rightSideWallLine[0], rightSideWallLine[1], rightWall[1]+5);

        if(distToRightOut < ballArray[0].ballRadius){
            scoreHandler(&ballArray[0]);
            //printf("R:::%f::%f\n",rightout,ballArray[0].ballRadius);
        }else{
            ballArray[0].currVel[2] = -ballArray[0].currVel[2] * dropOff;
            ballArray[0].currPos[2] += ballArray[0].ballRadius;
        }
    }

    //Roof
    if(ballArray[0].currPos[1] >= roof[0][1] - ballArray[0].ballRadius){

        resetFloorHitCount(&ballArray[0]);
        ballArray[0].currVel[1] = -ballArray[0].currVel[1];

        scoreHandler(&ballArray[0]);
    }

    ////make current position previous for next loop
    //position
    ballArray[0].prevPos[0] = ballArray[0].currPos[0];
    ballArray[0].prevPos[1] = ballArray[0].currPos[1];
    ballArray[0].prevPos[2] = ballArray[0].currPos[2];
    //velocity
    ballArray[0].prevVel[0] = ballArray[0].currVel[0];
    ballArray[0].prevVel[1] = ballArray[0].currVel[1];
    ballArray[0].prevVel[2] = ballArray[0].currVel[2];

    setPrevTime();

    glutPostRedisplay();
}

void initPhysics(){

    dropOff = defaultDropOff;
}

void hitBallForce(Point3D curVel, Point3D preVel, int i){

    curVel[0] = -curVel[0] - playerArray[i].powerLevel*hitSpeedX;
    preVel[0] = -preVel[0] - playerArray[i].powerLevel*hitSpeedX;


    preVel[1] = 0;
    preVel[1] = preVel[1] + 150.0 + playerArray[i].powerLevel*hitSpeedY;
        //Random used to move +ve or -ve or not at all in the Z direction
    preVel[2] = preVel[2] + playerArray[i].powerLevel*hitSpeedZ*round((2 * (rand() / (double) RAND_MAX) - 1));
}

void changeBallColor(ballObj *b){

    if(dropOff < maxDropOff){
        dropOff += dropOffIncreaseRate;
        b->ballColor[0] += colorChangeRate;
    }
}

void increaseBounciness(){

    if(dropOff < maxDropOff)
        dropOff += bounceIncreaseRate;
    else
        printf("Max bounciness reached");
}

void decreaseBounciness(){

    if(dropOff > minDropOff)
        dropOff -= bounceDecreaseRate;
    else
        printf("Min bounciness reached");
}
#endif //physics_H
