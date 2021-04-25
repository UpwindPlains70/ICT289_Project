#ifndef PLAYER_H
#define PLAYER_H

#include <GL/freeglut.h>
#include <GL/glut.h>

#include "Geometry.h"
#include "ReadOFFfile.h"

typedef struct player{
    Object3D charObj;
    Point3D CoM;
    float charHieght;
    float charRadius;

    Object3D handle;
    Object3D pad;
    Point3D handleCoM;
    Point3D padCoM;
}player;


void readCapsule(Object3D *obj)
{
    //char fileName[] = "objects/CapsuleV2.OFF";

    ReadOFFfile("objects/CapsuleV2.OFF", &obj);
}

void readBone(Object3D *obj)
{
    //char fileName[] = "objects/bone.OFF";

    ReadOFFfile("objects/bone.OFF", &obj);
    printf("read");
}

void readRacket_Zeroed(Object3D *obj)
{
    //char fileName[] = "objects/Racket_Zeroed.OFF";

    ReadOFFfile("objects/Racket_Zeroed.OFF", &obj);
}

void readRacket_Posed(Object3D *obj)
{
    //char fileName[] = "objects/Racket_Posed.OFF";

    ReadOFFfile("objects/Racket_Posed.OFF", &obj);
}

/*
void drawReadObject(Object3D obj)
{
    int i;
    for(i = 0; i < obj.nfaces; ++i)
    {
        Face3D f;

        f.x = obj.faces[i].x;
        f.y = obj.faces[i].y;
        f.z = obj.faces[i].z;

        glBegin(GL_TRIANGLES);
            glVertex3f(obj.vertices[f.x].x, obj.vertices[f.x].y, obj.vertices[f.x].z);
            glVertex3f(obj.vertices[f.y].x, obj.vertices[f.y].y, obj.vertices[f.y].z);
            glVertex3f(obj.vertices[f.z].x, obj.vertices[f.z].y, obj.vertices[f.z].z);
        glEnd();
    }
}
*/
/*
void myinit(void){
 // attributes
 glEnable(GL_DEPTH_TEST);
 glClearColor(0.0, 0.0, 0.0, 0.0); // draw on white background
 glLineWidth(5.0); // draw using lines 5 pixels wide

 // switch matrix mode to 'projection' and
 //load an identity matrix as the projection matrix
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();

        GLdouble fov	 = 60;		// degrees
        GLdouble aspect	 = 1;		// aspect ratio aspect = height/width
        GLdouble nearVal = 0.5;
        GLdouble farVal  = 100;     // near and far clipping planes
        gluPerspective(fov, aspect, nearVal, farVal);
 // switch matrix mode back to 'model view'
 glMatrixMode(GL_MODELVIEW);
}*/

#endif // PLAYER_H
