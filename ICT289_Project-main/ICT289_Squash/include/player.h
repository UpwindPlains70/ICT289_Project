#ifndef PLAYER_H
#define PLAYER_H

#include <GL/freeglut.h>
#include <GL/glut.h>

#include "Geometry.h"
#include "ReadOFFfile.h"

typedef enum {reset, hit, idle} swingStates; ///animation control states for character swing

typedef struct playerObj{
    Object3D charObj;
    Point3D CoM;
    float charHieght;
    float charRadius;

    Object3D handle;
    Object3D pad;
    Point3D handleCoM;
    Point3D padCoM;

    float currSwingAngle;
    swingStates swingMode;
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

    ///Swing animation parameters
#define TIMERMSECS 150 /// callback frequency
int maxSwingAngle = 60; ///Max swing angle of players
int swingSpeed = 80; ///speed of swing & reset

    //Cannot be moved to another file due to circular reference
void playerOneSwing(void){

    if(playerArray[0].swingMode != idle)
        glutTimerFunc(TIMERMSECS, playerOneSwing, 0);

    //Get elapsed time in seconds
    float currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    float timeSincePrevFrame = currTime - prevTime;

    //Update days

        ///First check for reset otherwise if not idle swing
    if(playerArray[0].currSwingAngle >= maxSwingAngle || playerArray[0].swingMode == reset && playerArray[0].swingMode != idle)
    {
        playerArray[0].swingMode = reset;
        playerArray[0].currSwingAngle -= swingSpeed * timeSincePrevFrame;
    }
    else if(playerArray[0].swingMode != idle)
    {
         playerArray[0].currSwingAngle += swingSpeed * timeSincePrevFrame;
    }

        ///Set swing mode to idle as animation has completed
    if(playerArray[0].currSwingAngle < 0.2 && playerArray[0].currSwingAngle > -0.2 && playerArray[0].swingMode == reset)
    {
        playerArray[0].swingMode = idle;
    }

    //save current time for use in next frame
    prevTime = currTime;

    glutPostRedisplay();
}

    //Cannot be moved to another file due to circular reference
void playerTwoSwing(void){

    if(playerArray[1].swingMode != idle)
        glutTimerFunc(TIMERMSECS, playerTwoSwing, 0);

    //Get elapsed time in seconds
    float currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    float timeSincePrevFrame = currTime - prevTime;

    //Update days

        ///First check for reset otherwise if not idle swing
    if(playerArray[1].currSwingAngle >= maxSwingAngle || playerArray[1].swingMode == reset && playerArray[1].swingMode != idle)
    {
        playerArray[1].swingMode = reset;
        playerArray[1].currSwingAngle -= swingSpeed * timeSincePrevFrame;
    }
    else if(playerArray[1].swingMode != idle)
    {
         playerArray[1].currSwingAngle += swingSpeed * timeSincePrevFrame;
    }

        ///Set swing mode to idle as animation has completed
    if(playerArray[1].currSwingAngle < 0.2 && playerArray[1].currSwingAngle > -0.2 && playerArray[1].swingMode == reset)
    {
        playerArray[1].swingMode = idle;
    }

    //save current time for use in next frame
    prevTime = currTime;

    glutPostRedisplay();
}

void movePlayerB()  // unsigned char key, int x, int y
{
   if(keyboardKeys['w']) moveLeft(&playerArray[1]);

    if(keyboardKeys['a']) moveBack(&playerArray[1]);

    if(keyboardKeys['s']) moveRight(&playerArray[1]);

    if(keyboardKeys['d']) moveForward(&playerArray[1]);

        //play hit animation
    if(keyboardKeys['f'])
    {
        playerArray[1].swingMode = hit; //hitting
        glutTimerFunc(TIMERMSECS, playerTwoSwing, 0);
    }

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

void pressedDown(unsigned char key, int x, int y)
{
    keyboardKeys[key] = TRUE;
    //glutPostRedisplay();
}

void pressedUp(unsigned char key, int x, int y)
{
    keyboardKeys[key] = FALSE;
    //glutPostRedisplay();
}

void movePlayerA()
{
        //UP
    if(arrowKeys[0]) moveLeft(&playerArray[0]);
        //left
    if(arrowKeys[1]) moveBack(&playerArray[0]);
        //down
    if(arrowKeys[2]) moveRight(&playerArray[0]);
        //right
    if(arrowKeys[3]) moveForward(&playerArray[0]);

        //swing
    if(keyboardKeys[' '])
    {
        playerArray[0].swingMode = hit; //hitting
        glutTimerFunc(TIMERMSECS, playerOneSwing, 0);
    }
	//glutPostRedisplay();
}

void moveForward(playerObj *obj) /// changing from using hard coded &playerA.charObj to the passed parameter
{
    obj->CoM[2] += -timeSincePrevFrame * speedMod;
}

void moveBack(playerObj *obj)
{
    obj->CoM[2] += timeSincePrevFrame * speedMod;
}

void moveLeft(playerObj *obj)
{
    obj->CoM[0] += -timeSincePrevFrame * speedMod;
}

void moveRight(playerObj *obj)
{
    obj->CoM[0] += timeSincePrevFrame * speedMod;
}
#endif // PLAYER_H
