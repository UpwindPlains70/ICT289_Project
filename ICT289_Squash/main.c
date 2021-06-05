#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif

#include "inputManager.h"
#include "include/ReadOFFfile.h"
#include "include/player.h"
#include "include/globals.h"
#include "include/menus.h"
#include "include/ObjectDisplay.h"

static const GLdouble viewer[]= {110.0, 40.0, -32.0, // initial camera location (across, up/down, distance to object)
                           0.0, 20.0, -32.0, // initial look at point
                           0.0, 1.0, 0.0};  // initial  upvector

    ///Perspective Camera specs
const GLdouble fov	 = 80;		// degrees
const GLdouble aspect	 = 1;		// aspect ratio aspect = height/width
const GLdouble nearVal = 0.1;
const GLdouble farVal  = 1000;     // near and far clipping planes

void myinit(void){

        /* attributes */
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0); /* draw on white background */
    glLineWidth(5.0); /* draw using lines 5 pixels wide */

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0,GL_POSITION,light_position);

        /* switch matrix mode to 'projection' and
            load an identity matrix as the projection matrix */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fov, aspect, nearVal, farVal);//*/
        /* switch matrix mode back to 'model view' */
    glMatrixMode(GL_MODELVIEW);
}

void reshape (int w, int h){
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(fov, (GLfloat) w/(GLfloat) h, nearVal, farVal);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    ///Set camera pos, look at, & up vec
    gluLookAt(viewer[0], viewer[1], viewer[2],
           viewer[3], viewer[4], viewer[5],
           viewer[6], viewer[7], viewer[8]);

        ///Enable shading from light
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_NORMALIZE);

    if(gameEnding == true){
        LoadImages(); ///Prevents game loading if done in myinit
        DrawGroupCred();
    }else{

        drawCourt();

        WriteScores();

        if(gameStarted == true)
            writeWhoseTurn();

            ///Show/hide menus
        menuHandler();

        calcTimeSinceLastFrame();
        setPrevTime();

        drawPowerBox();

        movePlayerB();
        movePlayerA();

        positionPlayer();
    }

    glDisable(GL_COLOR_MATERIAL);
    glutSwapBuffers();
}

    ///Read player objects
void read3DObjects(){

    for(int i = 0; i < maxPlayers; i++){
        ReadOFFfile("objects/Capsule.off", &playerArray[i].charObj);
        ReadOFFfile("objects/Racket_Handle.off", &playerArray[i].handle);
        ReadOFFfile("objects/Racket_Pad.off", &playerArray[i].pad);

        calcCenterOfMass(playerArray[i].charObj, playerArray[i].CoM ); /// added this each players COM
        calcCenterOfMass(playerArray[i].pad, playerArray[i].padCoM );
        calcCenterOfMass(playerArray[i].handle, playerArray[i].handleCoM );
    }
}

int main(int argc, char** argv){

    printf("Welcome to 'Squash Simulator'\n\n");
    printf("Right click game window for menu\n");

    read3DObjects();

    glutInit(&argc,argv); /* Standard GLUT initialization */

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB  | GLUT_DEPTH); //(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600); /* 500 x 500 pixel window */
    glutInitWindowPosition(0,0); /* place window top left on display */
    glutCreateWindow("Squash Simulator"); /* window title */

    glutIdleFunc(playerWallCollision);

    myinit(); /* set attributes */
    glutDisplayFunc(display); /* display callback invoked when window is opened */

    glutReshapeFunc(reshape);  ///Re scale window (prevent dispreportioned world)

    glutSpecialFunc(pressedSpecialDown); /// this function for arrow key movement
    glutSpecialUpFunc(pressedSpecialUp);
    glutKeyboardFunc(pressedDown);     /// this function for WASD movement, camera doesn't need to be manipulated by key press, camera can move by itself relative to the position of the ball maybe
    glutKeyboardUpFunc(pressedUp);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    //initPositions();
    createMainMenu(); ///GLUT menus
    glutMainLoop(); /* enter event loop */

 return 0;
}
