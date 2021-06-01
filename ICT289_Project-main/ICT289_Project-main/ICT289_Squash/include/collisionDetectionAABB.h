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



BOOLEAN collisionCheck(max max1, max max2, min min1, min min2){
    if((min1[0] <= max2[0] && max1[0] >= min2[0])&&(min1[1] <= max2[1] && max1[1] >= min2[1])&&(min1[2] <= max2[2] && max1[2] >= min2[2])){
        return TRUE;
    }else{
        return FALSE;
    }
}z

#endif // COLLISIONDETECTIONAABB_H_INCLUDED
