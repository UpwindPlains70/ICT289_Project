#ifndef INPUT_H
#define INPUT_H

#include "player.h"
#include "physics.h"
#include "scoreDisplay.h"

#include "globals.h"

BOOL keyboardKeys[256]; /// bool to know if a key is currently being pressed down or not, using this so both players can move at the same time
BOOL arrowKeys[4];

    ///Catch arrow key press
void pressedSpecialDown(int key, int x, int y){
    switch (key) {
		case GLUT_KEY_UP:
            arrowKeys[0] = TRUE;
		    break;

		case GLUT_KEY_LEFT:
		    arrowKeys[1] = TRUE;
		    break;

		case GLUT_KEY_DOWN:
            arrowKeys[2] = TRUE;
		    break;

		case GLUT_KEY_RIGHT:
            arrowKeys[3] = TRUE;
		    break;
	}
}

    ///Catch arrow key release
void pressedSpecialUp(int key, int x, int y){

    ///Catch normal key release

    switch (key) {
		case GLUT_KEY_UP:
            arrowKeys[0] = FALSE;
		    break;
		case GLUT_KEY_LEFT:
		    arrowKeys[1] = FALSE;
		    break;
		case GLUT_KEY_DOWN:
            arrowKeys[2] = FALSE;
		    break;
		case GLUT_KEY_RIGHT:
            arrowKeys[3] = FALSE;
		    break;
	}
}
void pressedUp(unsigned char key, int x, int y){
    keyboardKeys[key] = FALSE;

    if(key == 'f' || key == 'F')
    {
        playerArray[1].swingMode = hit;
        glutTimerFunc(TIMERMSECSB, playerTwoSwing, 0);
    }

    if(key == ' ')
    {
        playerArray[0].swingMode = hit;
        glutTimerFunc(TIMERMSECSA, playerOneSwing, 0);
    }
}

    ///Move player 1
void movePlayerA(){

        //UP
    if(arrowKeys[0]) moveLeft(&playerArray[0]);
        //left
    if(arrowKeys[1]) moveBack(&playerArray[0]);
        //down
    if(arrowKeys[2]) moveRight(&playerArray[0]);
        //right
    if(arrowKeys[3]) moveForward(&playerArray[0]);

    glutPostRedisplay();
}
    ///Move player 2
void movePlayerB(){  // unsigned char key, int x, int y
   if(keyboardKeys['w']) moveLeft(&playerArray[1]);

    if(keyboardKeys['a']) moveBack(&playerArray[1]);

    if(keyboardKeys['s']) moveRight(&playerArray[1]);

    if(keyboardKeys['d']) moveForward(&playerArray[1]);

    if(keyboardKeys['q']) exit(0);

    glutPostRedisplay();

}

void moveForward(playerObj *obj){ /// changing from using hard coded &playerA.charObj to the passed parameter

    obj->CoM[2] += -timeSincePrevFrame * speedMod;

    obj->padCoM[2] += -timeSincePrevFrame * speedMod;
}

void moveBack(playerObj *obj){

    obj->padCoM[2] += timeSincePrevFrame * speedMod;

    obj->CoM[2] += timeSincePrevFrame * speedMod;
}

void moveLeft(playerObj *obj){

    obj->CoM[0] += -timeSincePrevFrame * speedMod;

    obj->padCoM[0] += -timeSincePrevFrame * speedMod;
}

void moveRight(playerObj *obj){

    obj->CoM[0] += timeSincePrevFrame * speedMod;

    obj->padCoM[0] += timeSincePrevFrame * speedMod;
}


    ///Catch normal key press
void pressedDown(unsigned char key, int x, int y){

    keyboardKeys[key] = TRUE;

    if(key == 'f' || key == 'F')
        powerLevelHandler(&playerArray[1]);

    if(key == ' ')
        powerLevelHandler(&playerArray[0]);

        ///Lags physics too much
    if(optionsMenuActive == true){
        if(key == 'M')
            increasePlayerSpeed();
        if(key == 'm')
            decreasePlayerSpeed();

        if(key == 'N')
            increaseSwingSpeed();
        if(key == 'n')
            decreaseSwingSpeed();

        if(key == 'B')
            increaseBounciness();
        if(key == 'b')
            decreaseBounciness();

        if(key == 'V')
            increaseWinScore();
        if(key == 'v')
            decreaseWinScore();
    }
        ///Edit light position
    /*
    printf("light pos: x: %f, y:%f, z: %f\n", light_position[0], light_position[1], light_position[2]);
    if(keyboardKeys['t']) light_position[0]++;
    if(keyboardKeys['y']) light_position[1]++;
    if(keyboardKeys['u']) light_position[2]++;

    if(keyboardKeys['T']) light_position[0]--;
    if(keyboardKeys['Y']) light_position[1]--;
    if(keyboardKeys['U']) light_position[2]--;

    glLightfv(GL_LIGHT0,GL_POSITION,light_position);*/
}

#endif // INPUT_H
