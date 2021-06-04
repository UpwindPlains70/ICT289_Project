#include "player.h"

#include <GL/freeglut.h>
#include <GL/glut.h>

#include "Geometry.h"
#include "ReadOFFfile.h"


    //Cannot be moved to another file due to circular reference
void playerOneSwing(void){

    if(playerArray[0].swingMode != idle)
        glutTimerFunc(TIMERMSECS, playerOneSwing, 0);

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

//-27.000000, y:10.000000, z: -33
void movePlayerB()  // unsigned char key, int x, int y
{
   if(keyboardKeys['w']) moveLeft(&playerArray[1]);

    if(keyboardKeys['a']) moveBack(&playerArray[1]);

    if(keyboardKeys['s']) moveRight(&playerArray[1]);

    if(keyboardKeys['d']) moveForward(&playerArray[1]);

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
    //printf("light pos: x: %f, y:%f, z: %f\n", light_position[0], light_position[1], light_position[2]);
    keyboardKeys[key] = TRUE;
    //glutPostRedisplay();
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
    }

    /*if(keyboardKeys['t']) light_position[0]++;
    if(keyboardKeys['y']) light_position[1]++;
    if(keyboardKeys['u']) light_position[2]++;

    if(keyboardKeys['T']) light_position[0]--;
    if(keyboardKeys['Y']) light_position[1]--;
    if(keyboardKeys['U']) light_position[2]--;
*/
//    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
}

void pressedUp(unsigned char key, int x, int y)
{
    keyboardKeys[key] = FALSE;
    //glutPostRedisplay();
    if(key == 'f' || key == 'F')
    {
        //glutTimerFunc(TIMERMSECS, playerTwoPower, 0);
        playerArray[1].swingMode = hit;
        glutTimerFunc(TIMERMSECS, playerTwoSwing, 0);
    }

    if(key == ' ')
    {
        //glutTimerFunc(TIMERMSECS, playerTwoPower, 0);
        playerArray[0].swingMode = hit;
        glutTimerFunc(TIMERMSECS, playerOneSwing, 0);
    }
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

}

void moveForward(playerObj *obj) /// changing from using hard coded &playerA.charObj to the passed parameter
{
    obj->CoM[2] += -timeSincePrevFrame * speedMod;


    obj->padCoM[2] += -timeSincePrevFrame * speedMod;


}

void moveBack(playerObj *obj)
{
    obj->padCoM[2] += timeSincePrevFrame * speedMod;


    obj->CoM[2] += timeSincePrevFrame * speedMod;

}

void moveLeft(playerObj *obj)
{
    obj->CoM[0] += -timeSincePrevFrame * speedMod;


    obj->padCoM[0] += -timeSincePrevFrame * speedMod;

}

void moveRight(playerObj *obj)
{
    obj->CoM[0] += timeSincePrevFrame * speedMod;


    obj->padCoM[0] += timeSincePrevFrame * speedMod;

}

void drawPlayerTwoPower()
{
    glColor3f(0+playerArray[1].powerLevel/10.0,1-playerArray[1].powerLevel/10.0,0);
    glBegin(GL_POLYGON);
        glVertex3f(5,8,-57);
        glVertex3f(5,8,-52);
        glVertex3f(5,13,-52);
        glVertex3f(5,13,-57);
    glEnd();
}

void drawPlayerOnePower()
{
    glColor3f(0+playerArray[0].powerLevel/10.0,1-playerArray[0].powerLevel/10.0,0);
    glBegin(GL_POLYGON);
        glVertex3f(5,8,-5);
        glVertex3f(5,8,-10);
        glVertex3f(5,13,-10);
        glVertex3f(5,13,-5);
    glEnd();
}

void increasePlayerSpeed()
{
    if(speedMod < maxSpeedMod)
        speedMod++; ///Increase speed by one
    else
        printf("Player speed is at maximum: %f\n", speedMod);
}

void decreasePlayerSpeed()
{
    if(speedMod > minSpeedMod)
        speedMod--; ///Increase speed by one
    else
        printf("Player speed is at minimum: %f\n", speedMod);
}


void increaseSwingSpeed()
{
    if(swingSpeed < maxSwingSpeed)
        swingSpeed++;
    else
        printf("Swing speed is at maximum: %f\n", swingSpeed);
}

void decreaseSwingSpeed()
{
    if(swingSpeed > minSwingSpeed)
        swingSpeed--;
    else
        printf("Swing speed is at minimum: %f\n", swingSpeed);
}

void resetPlayerPos()
{
    for(int i = 0; i < 2; i++){
        playerArray[i].CoM[0] = playerArray[i].startPos[0];
        //playerArray[i].CoM[1] = playerArray[i].startPos[1]  +2.0* playerArray[i].charHieght;
        playerArray[i].CoM[2] = playerArray[i].startPos[2];
    }
}
