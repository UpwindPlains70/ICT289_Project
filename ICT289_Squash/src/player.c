#include "../include/player.h"

#include <stdio.h>
#include "Geometry.h"
#include "globals.h"


void drawPlayer(int i, GLdouble colour[]){
//Draw player (Capsule)

    glColor3f(colour[0], colour[1], colour[2]);   // 0.4, 0.1, 0.1
    glScaled(0.02,0.02,0.02);
    draw3DObject(playerArray[i].charObj);

}

void drawRacket(int i){

 //Draw racket
    //glRotatef(90, 0, 1,0);
    glColor3f(0.6, 0.2, 0.2);
    draw3DObject(playerArray[i].handle);
    glColor3f(0.7,0.7,0.7);
    draw3DObject(playerArray[i].pad);

}

    //Cannot be reused as animation functions can only have void parameter
void playerOneSwing(void){

    if(playerArray[0].swingMode != idle)
        glutTimerFunc(TIMERMSECSA, playerOneSwing, 0);

    //Get elapsed time in seconds
    float currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    float timeSincePrevFrame = currTime - prevTime;

    //Update days

        ///First check for reset otherwise if not idle swing
    if((playerArray[0].currSwingAngle >= maxSwingAngle) || ((playerArray[0].swingMode == reset) && (playerArray[0].swingMode != idle)))
    {
        playerArray[0].swingMode = reset;
        playerArray[0].currSwingAngle -= swingSpeed * timeSincePrevFrame * playerArray[0].powerLevel;
    }
    else if(playerArray[0].swingMode != idle)
    {
         playerArray[0].currSwingAngle += swingSpeed * timeSincePrevFrame * playerArray[0].powerLevel;
    }

        ///Set swing mode to idle as animation has completed
    if(playerArray[0].currSwingAngle < 0 && playerArray[0].swingMode == reset)
    {
        playerArray[0].swingMode = idle;
        playerArray[0].powerLevel = 1;
    }

    //save current time for use in next frame
    prevTime = currTime;

    glutPostRedisplay();
}

    //Cannot be reused as animation functions can only have void parameter
void playerTwoSwing(void){

    if(playerArray[1].swingMode != idle)
        glutTimerFunc(TIMERMSECSB, playerTwoSwing, 0);

    //Get elapsed time in seconds
    float currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    float timeSincePrevFrame = currTime - prevTime;

    //Update days

        ///First check for reset otherwise if not idle swing
    if(playerArray[1].currSwingAngle >= maxSwingAngle || playerArray[1].swingMode == reset && playerArray[1].swingMode != idle)
    {
        playerArray[1].swingMode = reset;
        playerArray[1].currSwingAngle -= swingSpeed * timeSincePrevFrame * playerArray[1].powerLevel;
    }
    else if(playerArray[1].swingMode != idle)
    {
         playerArray[1].currSwingAngle += swingSpeed * timeSincePrevFrame * playerArray[1].powerLevel;
    }

        ///Set swing mode to idle as animation has completed
    if(playerArray[1].currSwingAngle < 0 && playerArray[1].swingMode == reset)
    {
        playerArray[1].swingMode = idle;
        playerArray[1].powerLevel = 1;
    }

    //save current time for use in next frame
    prevTime = currTime;

    glutPostRedisplay();
}

void movePlayerB(){  // unsigned char key, int x, int y
   if(keyboardKeys['w']) moveLeft(&playerArray[1]);

    if(keyboardKeys['a']) moveBack(&playerArray[1]);

    if(keyboardKeys['s']) moveRight(&playerArray[1]);

    if(keyboardKeys['d']) moveForward(&playerArray[1]);

    if(keyboardKeys['q']) exit(0);

    glutPostRedisplay();

}

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

void pressedSpecialUp(int key, int x, int y){

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

void pressedDown(unsigned char key, int x, int y){

    keyboardKeys[key] = TRUE;

    if(key == 'f' || key == 'F')
    {
        if(playerArray[1].swingMode != cooling || playerArray[1].powerLevel == 1)
            playerArray[1].swingMode = powering;

        if(playerArray[1].powerLevel < 10 && playerArray[1].swingMode != cooling)
            playerArray[1].powerLevel++;
        else{
            playerArray[1].powerLevel--;
            playerArray[1].swingMode = cooling;
        }
    }

    if(key == ' ')
    {
        if(playerArray[0].swingMode != cooling || playerArray[0].powerLevel == 1)
            playerArray[0].swingMode = powering;

        if(playerArray[0].powerLevel < 10 && playerArray[0].swingMode != cooling)
            playerArray[0].powerLevel++;
        else{
            playerArray[0].powerLevel--;
            playerArray[0].swingMode = cooling;
        }
        glutPostRedisplay();
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

    if(keyboardKeys['1']) printf("num pes");
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

void drawPlayerTwoPower(){

    glColor3f(0+playerArray[1].powerLevel/10.0,1-playerArray[1].powerLevel/10.0,0);
    glBegin(GL_POLYGON);
        glVertex3f(5,8,-57);
        glVertex3f(5,8,-52);
        glVertex3f(5,13,-52);
        glVertex3f(5,13,-57);
    glEnd();
}

void drawPlayerOnePower(){

    glColor3f(0+playerArray[0].powerLevel/10.0,1-playerArray[0].powerLevel/10.0,0);
    glBegin(GL_POLYGON);
        glVertex3f(5,8,-5);
        glVertex3f(5,8,-10);
        glVertex3f(5,13,-10);
        glVertex3f(5,13,-5);
    glEnd();
}

void increasePlayerSpeed(){

    if(speedMod < maxSpeedMod)
        speedMod++; ///Increase speed by one
    else
        printf("Player speed is at maximum: %f\n", speedMod);
}

void decreasePlayerSpeed(){

    if(speedMod > minSpeedMod)
        speedMod--; ///Increase speed by one
    else
        printf("Player speed is at minimum: %f\n", speedMod);
}

void increaseSwingSpeed(){

    if(swingSpeed < maxSwingSpeed)
        swingSpeed++;
    else
        printf("Swing speed is at maximum: %f\n", swingSpeed);
}

void decreaseSwingSpeed(){

    if(swingSpeed > minSwingSpeed)
        swingSpeed--;
    else
        printf("Swing speed is at minimum: %f\n", swingSpeed);
}

void resetPlayerPos(){

    for(int i = 0; i < maxPlayers; i++){
        playerArray[i].CoM[0] = playerArray[i].startPos[0];

        playerArray[i].CoM[2] = playerArray[i].startPos[2];
    }
}
