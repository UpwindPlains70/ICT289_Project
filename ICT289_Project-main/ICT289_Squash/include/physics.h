#ifndef PHYSICS_H
#define PHYSICS_H

#include "ball.h"
#include "player.h"
#include "collisionDetectionAABB.h"
#include "Room.h"

//animation timers
float startTime, prevTime;

//level of energy loss
float dropOff = 0.75;
// gravity (earth) (affects velocity)
Point3D g = {0, -980, 0};

//initial velocity for x,y,z directions
Point3D v0 ={100, 0, 0}; /// changing from 250 x
//current and previous velocity
Point3D currVel, prevVel;

BOOL hitBackWall = FALSE;

max maP1,maP2;
min miP1,miP2;

void resetPhysics()
{

}
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
        //currVel[1] = currVel[1]/2.5;
    }
    //front (Wall with score)
    if (currPos[0] <= 0.0){
        currPos[0] = 0.0;
        currVel[0] = -currVel[0];
        currVel[1] = -currVel[1] * dropOff;
        hitBackWall = TRUE;
        changeBallColor(); //increase ball color (RED) & bounsiness
    }
    //left
    if (currPos[2] >= 0 ){
        currVel[2] = -currVel[2];
        currPos[2] -= ballRadius;
    }
    //right
    if (currPos[2] <= -64 ){
        currVel[2] = -currVel[2];
        currPos[2] += ballRadius;
    }

    //Roof
    if(currPos[1] >= 56.4)
    {
        currPos[1] = 50;
        currVel[1] = -currVel[1] * dropOff;
        hitBackWall = TRUE;
    }

    //Reset y posistion if ball is sliding on the floor
    /*if(currPos[1] <= prevPos[1] + 0.001 && currPos[1] >= prevPos[1] - 0.001)
       {
           printf("reset");
           currPos[1] = startPos[1];
       }*/

    //racket collision
    //racketCollision(currPos);


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
    dropOff = 0.75;
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

///Used by display callback function in main
void collisions(int i){

        rackPos[i][0] = startingPos[i][0]  + playerArray[i].CoM[0];
        rackPos[i][1] = playerArray[i].CoM[1];
        rackPos[i][2] = startingPos[i][2] + playerArray[i].CoM[2];

      //  printf("Racket Position: %f %f %f \n", rackPos[0], rackPos[1], rackPos[2]);
       // printf("Ball Position: %f %f %f \n", currPos[0], currPos[1], currPos[2]);
        vecRackToBall[0] = currPos[0] - rackPos[i][0];
        vecRackToBall[1] = currPos[1] - rackPos[i][1];
        vecRackToBall[2] = currPos[2] - rackPos[i][2];

     if((vecRackToBall[0] <= 10 && vecRackToBall[0] >= -10) && (vecRackToBall[2] <= 10 && vecRackToBall[2] >= -10) && (vecRackToBall[1] <= 10 && vecRackToBall[1] >= -10) ){
           // printf("COllisions!\n");
            currVel[0] = (currVel[0])* -1;
            prevVel[0] = (prevVel[0])* -1.001;// * playerArray[i].powerLevel;

            //prevPos[0] = prevPos[0] - 10;
            //prevVel[1] = prevVel[1]/0.1;///Take previous increase off before adding
                prevVel[1] = 0;
                prevVel[1] = prevVel[1] + 150.0 + playerArray[i].powerLevel*15;
                prevVel[2] = prevVel[2] + playerArray[i].powerLevel*5;
            hasHitBall[i] = TRUE;
        }
}

void changeBallColor()
{
    if(dropOff > 0.50)
       dropOff -= 0.05;

    ballColor[0] += 0.2;
}
#endif //physics_H
