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

    ///Rate of ball color change
const float colorChangeRate = 0.2;

float distToLeftOut;
float distToRightOut;
// gravity (earth) (affects velocity)
Point3D g = {0, -980, 0};

    ///Player hit velocity multipliers/values
const float hitSpeedX = 20.0;
const float hitSpeedY = 15.0;
const float hitSpeedZ = 1.2;
const float setYincreaseOnHit = 150.0;

    ///Rate of increase/decrease for customization
const float bounceIncreaseRate = 0.1;
const float bounceDecreaseRate = 0.1;

//animation
void physics(void){

        //Only run while game has started
    if(gameStarted == true)
        glutTimerFunc(TIMER, physics, 0);

    calcTimeSinceLastFrame();

        //Apply Gravity to ball
    ballArray[0].currPos[0] = ballArray[0].prevPos[0] + (ballArray[0].prevVel[0] * timeSincePrevFrame) + (g[0] * timeSincePrevFrame * timeSincePrevFrame / 2);
    ballArray[0].currPos[1] = ballArray[0].prevPos[1] + (ballArray[0].prevVel[1] * timeSincePrevFrame) + (g[1] * timeSincePrevFrame * timeSincePrevFrame / 2);
    ballArray[0].currPos[2] = ballArray[0].prevPos[2] + (ballArray[0].prevVel[2] * timeSincePrevFrame) + (g[2] * timeSincePrevFrame * timeSincePrevFrame / 2);

        //find ball velocity
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

    //back wall collision (no loss of energy, as ball can go out of frame)
    if (ballArray[0].currPos[0] >= gamefloor[2][0]){
        ballArray[0].currVel[0] = -ballArray[0].currVel[0];

        resetFloorHitCount(&ballArray[0]);
    }

    //front (Wall with score) collision
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

   //left wall collision
    if (ballArray[0].currPos[2] >= gamefloor[0][0] - ballArray[0].ballRadius){

        resetFloorHitCount(&ballArray[0]);
        distToLeftOut = distanceFromSphereToPlane(ballArray[0].currPos, leftSideWallLine[0], leftSideWallLine[1], leftWall[1]-10);
            //Check if ball is out (above line)
        if(distToLeftOut < ballArray[0].ballRadius){
            scoreHandler(&ballArray[0]);
        }else{
            ballArray[0].currVel[2] = -ballArray[0].currVel[2] * dropOff;
            ballArray[0].currPos[2] -= ballArray[0].ballRadius;
        }
    }

    //right wall colision
    if (ballArray[0].currPos[2] <= gamefloor[1][2] + ballArray[0].ballRadius){

        resetFloorHitCount(&ballArray[0]);
        distToRightOut = distanceFromSphereToPlane(ballArray[0].currPos, rightSideWallLine[0], rightSideWallLine[1], rightWall[1]+5);
            //Check if ball is out (above line)
        if(distToRightOut < ballArray[0].ballRadius){
            scoreHandler(&ballArray[0]);
        }else{
            ballArray[0].currVel[2] = -ballArray[0].currVel[2] * dropOff;
            ballArray[0].currPos[2] += ballArray[0].ballRadius;
        }
    }

    //Roof collision
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

    ///Set physics value (drop off only)
    //All balls retain their own physics values (allows for different behaviours)
void initPhysics(){

    dropOff = defaultDropOff;
}

    ///Force added by player on hit
void hitBallForce(Point3D curVel, Point3D preVel, int i){

        ///Change direction of ball (opposite)
    curVel[0] = -curVel[0] - playerArray[i].powerLevel*hitSpeedX;
    preVel[0] = -preVel[0] - playerArray[i].powerLevel*hitSpeedX;

        ///increase Y velocity
    preVel[1] = 0;
    preVel[1] = preVel[1] + setYincreaseOnHit + playerArray[i].powerLevel*hitSpeedY;
        ///Increase Z velocity
        //Random used to move +ve or -ve or not at all in the Z direction
    preVel[2] = preVel[2] + playerArray[i].powerLevel*hitSpeedZ*round((2 * (rand() / (double) RAND_MAX) - 1));
}

    ///Controlled animation indicating bounciness of ball
    //Redder = bouncier, black = not bouncy
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
