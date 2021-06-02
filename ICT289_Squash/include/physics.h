#ifndef PHYSICS_H
#define PHYSICS_H

#include "ball.h"
#include "player.h"
#include "collisionDetectionAABB.h"
#include "Room.h"

//animation timers
float startTime, prevTime;

//level of energy loss
float dropOff = 0.55;
// gravity (earth) (affects velocity)
Point3D g = {0, -980, 0};

//initial velocity for x,y,z directions
Point3D v0 ={100, 0, 0}; /// changing from 250 x
//current and previous velocity
///Point3D currVel, prevVel;





max maP1,maP2;
min miP1,miP2;

void playerWallCollision();

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
    ballArray[0].currPos[0] = ballArray[0].prevPos[0] + (ballArray[0].prevVel[0] * timePrevCur) + (g[0] * timePrevCur * timePrevCur / 2);
    ballArray[0].currPos[1] = ballArray[0].prevPos[1] + (ballArray[0].prevVel[1] * timePrevCur) + (g[1] * timePrevCur * timePrevCur / 2);
    ballArray[0].currPos[2] = ballArray[0].prevPos[2] + (ballArray[0].prevVel[2] * timePrevCur) + (g[2] * timePrevCur * timePrevCur / 2);

    //find velocity
    ballArray[0].currVel[0] = ballArray[0].prevVel[0] + (g[0] * timePrevCur);
    ballArray[0].currVel[1] = ballArray[0].prevVel[1] + (g[1] * timePrevCur);
    ballArray[0].currVel[2] = ballArray[0].prevVel[2] + (g[2] * timePrevCur);

    //energy drop off when collision occurs
    //floor collision
    if (ballArray[0].currPos[1] <= ballArray[0].ballRadius){
        ballArray[0].currVel[1] = -ballArray[0].currVel[1] * dropOff;
        ballArray[0].currPos[1] = ballArray[0].ballRadius;
    }

    ////wall collisions
    //back
    if (ballArray[0].currPos[0] >= (54.4 + 16.0 + 26.1)){
        ballArray[0].currVel[0] = -ballArray[0].currVel[0];
        //currVel[1] = currVel[1]/2.5;
    }
    //front (Wall with score)
    if (ballArray[0].currPos[0] <= 0.0){
        ballArray[0].currPos[0] = 0.0;
        ballArray[0].currVel[0] = -ballArray[0].currVel[0];
        ballArray[0].currVel[1] = -ballArray[0].currVel[1] * dropOff;
        hitBackWall = TRUE;
        changeBallColor(); //increase ball color (RED) & bounsiness
    }
    //left
    if (ballArray[0].currPos[2] >= 0 ){
        ballArray[0].currVel[2] = -ballArray[0].currVel[2];
        ballArray[0].currPos[2] -= ballArray[0].ballRadius;
    }
    //right
    if (ballArray[0].currPos[2] <= -64 ){
        ballArray[0].currVel[2] = -ballArray[0].currVel[2];
        ballArray[0].currPos[2] += ballArray[0].ballRadius;
    }

    //Roof
    if(ballArray[0].currPos[1] >= 56.4)
    {
        ballArray[0].currPos[1] = 50;
        ballArray[0].currVel[1] = -ballArray[0].currVel[1] * dropOff;
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
    playerWallCollision();

    ////make current position previous for next loop
    //position
    ballArray[0].prevPos[0] = ballArray[0].currPos[0];
    ballArray[0].prevPos[1] = ballArray[0].currPos[1];
    ballArray[0].prevPos[2] = ballArray[0].currPos[2];
    //velocity
    ballArray[0].prevVel[0] = ballArray[0].currVel[0];
    ballArray[0].prevVel[1] = ballArray[0].currVel[1];
    ballArray[0].prevVel[2] = ballArray[0].currVel[2];
    //time
    prevTime = currTime;

    glutPostRedisplay();
}

void initPositions(){
    dropOff = 0.75;
    ballArray[0].currPos[0] = startPos[0];
    ballArray[0].currPos[1] = startPos[1];
    ballArray[0].currPos[2] = startPos[2];
    ballArray[0].prevPos[0] = startPos[0];
    ballArray[0].prevPos[1] = startPos[1];
    ballArray[0].prevPos[2] = startPos[2];
    //velocity/s
    ballArray[0].prevVel[0] = v0[0];
    ballArray[0].prevVel[1] = v0[1];
    ballArray[0].prevVel[2] = v0[2];
    ballArray[0].currVel[0] = v0[0];
    ballArray[0].currVel[1] = v0[1];
    ballArray[0].currVel[2] = v0[2];
}



void hitBallForce(Point3D curVel, Point3D preVel, int i){

     curVel[0] = (curVel[0]) * -1;
     preVel[0] = (preVel[0]) * -1.001;// * playerArray[i].powerLevel;

    //prevPos[0] = prevPos[0] - 10;
    //prevVel[1] = prevVel[1]/0.1;///Take previous increase off before adding

    preVel[1] = 0;
    preVel[1] = preVel[1] + 150.0 + playerArray[i].powerLevel*15.0;




     //*preVel[2] = *preVel[2] + playerArray[i].powerLevel*5;


}


void changeBallColor()
{
    if(dropOff > 0.90)
       dropOff += 0.05;

    ballArray[0].ballColor[0] += 0.2;
}
#endif //physics_H
