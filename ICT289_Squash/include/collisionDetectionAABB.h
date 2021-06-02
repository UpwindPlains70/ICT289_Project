#ifndef COLLISIONDETECTIONAABB_H_INCLUDED
#define COLLISIONDETECTIONAABB_H_INCLUDED
#include <GL/freeglut.h>
#include "Geometry.h"

typedef int max[3]; // changing from size 2 to size 3
typedef int min[3];
max ma1,ma2;
min mi1,mi2;

GLfloat maxYFloat; /// use this make sure player isn't halfway through the ground
GLfloat minYFloat;


const XcollisionBox = 10;
const YcollisionBox = 10;
const ZcollisionBox = 10;

BOOL hitBackWall = FALSE;


///Used by display callback function in main
void collisions(int i, ballObj *b){
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


            hitBallForce(b->currVel, b->prevVel, i); /// function in physics to apply force
            hasHitBall[i] = TRUE;
        }


}

void playerWallCollision(){
    //none of these make any sense until you see how they move
    for(int i = 0; i < 2; i++){
        //back
        if (playerArray[i].CoM[0] > 20){
            playerArray[i].CoM[0] = 20;
        }
        //front
        if (playerArray[i].CoM[0] < -55){
            playerArray[i].CoM[0] = -55;
        }
        //left
        if(i==0){
            if(playerArray[i].CoM[2] > 5){
                playerArray[i].CoM[2] = 5;
            }
        }else if(i==1){
            if(playerArray[i].CoM[2] > 50){
                playerArray[i].CoM[2] = 50;
            }
        }
        //right
        if(i==0){
            if(playerArray[i].CoM[2] < -50){
                playerArray[i].CoM[2] = -50;
            }
        }else if(i==1){
            if(playerArray[i].CoM[2] < -5){
                playerArray[i].CoM[2] = -5;
            }
        }
        //if(playerArray[i].CoM[2] < ){
            //playerArray[i].CoM[2] = -64;
        //}
    }
}




void getMaxMin(Object3D bone,max ma, min mi){
    unsigned xMax=0;
    unsigned yMax=0;
    unsigned zMax=0;
    unsigned xMin=bone.vertices[0][0];
    unsigned yMin=bone.vertices[0][1];
    unsigned zMin=bone.vertices[0][2];

    maxYFloat = 0.0;
    minYFloat = 0.0;

    for(int i = 0; i < bone.nverts; i++){
            if(bone.vertices[i][0] >= xMax){
                xMax = bone.vertices[i][0];
            }else if(bone.vertices[i][0] < xMin){
                xMin = bone.vertices[i][0];
            }

            if(bone.vertices[i][1] >= yMax){
                yMax = bone.vertices[i][1];
                maxYFloat = bone.vertices[i][1];
            }else if(bone.vertices[i][1] >= yMin){
                yMin = bone.vertices[i][1];
                minYFloat = bone.vertices[i][1];
            }

            if(bone.vertices[i][2] >= zMax){
                zMax = bone.vertices[i][2];
            }else if(bone.vertices[i] >= zMin){
                zMin = bone.vertices[i][2];
            }

    }
    ma[0] = xMax;
    ma[1] = yMax;
    ma[2] = zMax;
    mi[0] = xMin;
    mi[1] = yMin;
    mi[2] = zMin;
}





#endif // COLLISIONDETECTIONAABB_H_INCLUDED
