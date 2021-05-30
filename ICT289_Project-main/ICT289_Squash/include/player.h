#ifndef PLAYER_H
#define PLAYER_H

#include <GL/freeglut.h>
#include <GL/glut.h>

#include "Geometry.h"
#include "ReadOFFfile.h"

typedef struct playerObj{
    Object3D charObj;
    Point3D CoM;
    float charHieght;
    float charRadius;

    Object3D handle;
    Object3D pad;
    Point3D handleCoM;
    Point3D padCoM;
}playerObj;

playerObj playerA;
playerObj playerB;

float movementSpeed = 20.0f;

void movePlayerB(unsigned char key, int x, int y)
{
    if(key == 'w' || key == 'W') moveForward(&playerB);

    if(key == 'a' || key == 'A') moveLeft(&playerB);

    if(key == 's' || key == 'S') moveBack(&playerB);

    if(key == 'd' || key == 'D') moveRight(&playerB);

        //play hit animation
    if(key == 'f' || key == 'F'){}

    if(key =='q' || key == 'Q') exit(0);
    glutPostRedisplay();
}

void movePlayerA(int key, int x, int y)
{
    switch (key) {
		case GLUT_KEY_UP:
            moveForward(&playerA);
		    break;
		case GLUT_KEY_LEFT:
		    moveLeft(&playerA);
		    break;
		case GLUT_KEY_DOWN:
            moveBack(&playerA);
		    break;
		case GLUT_KEY_RIGHT:
		    moveRight(&playerA);
		    break;
        //hit key for player A
	}

	glutPostRedisplay();
}

void moveForward(playerObj *obj)
{
    translate3DObject(&playerA.charObj, 0, 0, -movementSpeed);
    translate3DObject(&playerA.handle, 0, 0, -movementSpeed);
    translate3DObject(&playerA.pad, 0, 0, -movementSpeed);
}

void moveBack(playerObj *obj)
{
    translate3DObject(&playerA.charObj, 0, 0, movementSpeed);
    translate3DObject(&playerA.handle, 0, 0, movementSpeed);
    translate3DObject(&playerA.pad, 0, 0, movementSpeed);
}

void moveLeft(playerObj *obj)
{
    translate3DObject(&playerA.charObj, -movementSpeed, 0,0);
    translate3DObject(&playerA.handle, -movementSpeed, 0,0);
    translate3DObject(&playerA.pad, -movementSpeed, 0,0);
}

void moveRight(playerObj *obj)
{
    translate3DObject(&playerA.charObj, movementSpeed, 0,0);
    translate3DObject(&playerA.handle, movementSpeed, 0,0);
    translate3DObject(&playerA.pad, movementSpeed, 0,0);
}
#endif // PLAYER_H
