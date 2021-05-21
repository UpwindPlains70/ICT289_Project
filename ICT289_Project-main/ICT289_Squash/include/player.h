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

//playerObj playerA;      // using the array of playerObj instead by referring to [0] and [1] for playerA and playerB
//playerObj playerB;

float startTime, prevTime;
float currTime;
float timeSincePrevFrame;

float speedMod = 40; /// control the speed of all the movements

BOOL keyboardKeys[256]; /// bool to know if a key is currently being pressed down or not, using this so both players can move at the same time
BOOL arrowKeys[4];

typedef GLdouble Colours[3];
Colours playerColours[2];

playerObj playerArray[2];


float movementSpeed = 20.0f;

void movePlayerB()  // unsigned char key, int x, int y
{
   // if(key == 'w' || key == 'W'){
   if(keyboardKeys['w']) moveForward(&playerArray[1]);



    // key == 'a' || key == 'A'
    if(keyboardKeys['a']) moveLeft(&playerArray[1]);
    // key == 's' || key == 'S'
    if(keyboardKeys['s']) moveBack(&playerArray[1]);
    //key == 'd' || key == 'D'
    if(keyboardKeys['d']) moveRight(&playerArray[1]);
    // glutPostRedisplay();


        //play hit animation
   // if(key == 'f' || key == 'F'){}

    if(keyboardKeys['q']) exit(0);

    //glutPostRedisplay();

}

void pressedSpecialDown(int key, int x, int y){

    switch (key) {
		case GLUT_KEY_UP:
           // moveForward(&playerArray[0]);
            arrowKeys[0] = TRUE;
		    break;

		case GLUT_KEY_LEFT:
		   // moveLeft(&playerArray[0]);
		    arrowKeys[1] = TRUE;
		    break;

		case GLUT_KEY_DOWN:
          //  moveBack(&playerArray[0]);
            arrowKeys[2] = TRUE;
		    break;

		case GLUT_KEY_RIGHT:
		   // moveRight(&playerArray[0]);
            arrowKeys[3] = TRUE;
		    break;


        //hit key for player A
	}

	 //glutPostRedisplay();

}

void pressedSpecialUp(int key, int x, int y){

    switch (key) {
		case GLUT_KEY_UP:
           // moveForward(&playerArray[0]);
            arrowKeys[0] = FALSE;
		    break;
		case GLUT_KEY_LEFT:
		   // moveLeft(&playerArray[0]);
		    arrowKeys[1] = FALSE;
		    break;
		case GLUT_KEY_DOWN:
          //  moveBack(&playerArray[0]);
            arrowKeys[2] = FALSE;
		    break;
		case GLUT_KEY_RIGHT:
		   // moveRight(&playerArray[0]);
            arrowKeys[3] = FALSE;
		    break;


        //hit key for player A
	}

    //glutPostRedisplay();
}

void pressedDown(unsigned char key, int x, int y){



 keyboardKeys[key] = TRUE;
 //glutPostRedisplay();





}
void pressedUp(unsigned char key, int x, int y){

    keyboardKeys[key] = FALSE;
    //glutPostRedisplay();

}

void movePlayerA()
{

    if(arrowKeys[0]) moveForward(&playerArray[0]);

    if(arrowKeys[1]) moveLeft(&playerArray[0]);

    if(arrowKeys[2]) moveBack(&playerArray[0]);

    if(arrowKeys[3]) moveRight(&playerArray[0]);



	//glutPostRedisplay();
}

void moveForward(playerObj *obj) /// changing from using hard coded &playerA.charObj to the passed parameter
{
    translate3DObject(&obj->charObj, 0, 0, -movementSpeed * timeSincePrevFrame * speedMod);
    translate3DObject(&obj->handle, 0, 0, -movementSpeed * timeSincePrevFrame * speedMod);
    translate3DObject(&obj->pad, 0, 0, -movementSpeed * timeSincePrevFrame * speedMod);
}

void moveBack(playerObj *obj)
{
    translate3DObject(&obj->charObj, 0, 0, movementSpeed * timeSincePrevFrame * speedMod);
    translate3DObject(&obj->handle, 0, 0, movementSpeed * timeSincePrevFrame * speedMod);
    translate3DObject(&obj->pad, 0, 0, movementSpeed * timeSincePrevFrame * speedMod);
}

void moveLeft(playerObj *obj)
{
    translate3DObject(&obj->charObj, -movementSpeed * timeSincePrevFrame * speedMod, 0,0);
    translate3DObject(&obj->handle, -movementSpeed * timeSincePrevFrame * speedMod, 0,0);
    translate3DObject(&obj->pad, -movementSpeed * timeSincePrevFrame * speedMod, 0,0);
}

void moveRight(playerObj *obj)
{
    translate3DObject(&obj->charObj, movementSpeed * timeSincePrevFrame * speedMod, 0,0);
    translate3DObject(&obj->handle, movementSpeed * timeSincePrevFrame * speedMod, 0,0);
    translate3DObject(&obj->pad, movementSpeed * timeSincePrevFrame * speedMod, 0,0);
}
#endif // PLAYER_H
