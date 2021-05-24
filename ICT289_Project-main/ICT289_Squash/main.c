#include <stdio.h>
#include <stdlib.h>

#include "include/Geometry.h"
#include "include/ReadOFFfile.h"
#include "include/player.h"
#include "include/Room.h"
#include "include/collisionDetectionAABB.h"

#include <GL/freeglut.h>
#include <GL/glut.h>

#define TIMER 10


static GLdouble viewer[]= {110.0, 40.0, -32.0, // initial camera location (across, up/down, distance to object)
                           0.0, 20.0, -32.0, // initial look at point
                           0.0, 1.0, 0.0};  // initial  upvector

void myinit(void){
 /* attributes */
  glEnable(GL_DEPTH_TEST);
 glClearColor(1.0, 1.0, 1.0, 1.0); /* draw on white background */
 glColor3f(1.0, 0.0, 0.0); /* draw in red */
 glLineWidth(5.0); /* draw using lines 5 pixels wide */

 /* switch matrix mode to 'projection' and
 load an identity matrix as the projection matrix */
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();

        GLdouble fov	 = 80;		// degrees
        GLdouble aspect	 = 1;		// aspect ratio aspect = height/width
        GLdouble nearVal = 0.1;
        GLdouble farVal  = 1000;     // near and far clipping planes
        gluPerspective(fov, aspect, nearVal, farVal);//*/
 /* switch matrix mode back to 'model view' */
 glMatrixMode(GL_MODELVIEW);
}


void drawPlayer(int i, GLdouble colour[]){
//Draw player (Capsule)
    glColor3f(colour[0], colour[1], colour[2]);   // 0.4, 0.1, 0.1
    glScaled(0.02,0.02,0.02);
    draw3DObject(playerArray[i].charObj);

}

void drawRacket(int i){

 //Draw racket
    glColor3f(0.6, 0.2, 0.2);
    draw3DObject(playerArray[i].handle);
    glColor3f(0.7,0.7,0.7);
    draw3DObject(playerArray[i].pad);

}

void drawAxis(){
    Point3D axisVerts[4] = {{0.0, 0.0, 0.0},
                          {500.0, 0.0, 0.0},
                          {0.0, 500.0, 0.0},
                          {0.0, 0.0, 500.0}};

    glBegin(GL_LINE_LOOP);//Draws x axis
        glColor3f(1,0,0);
        glVertex3fv(axisVerts[0]);
        glVertex3fv(axisVerts[1]);
    glEnd();

    glBegin(GL_LINE_LOOP);//Draws y axis
        glColor3f(0,1,0);
        glVertex3fv(axisVerts[0]);
        glVertex3fv(axisVerts[2]);
    glEnd();

    glBegin(GL_LINE_LOOP);//Draws z axis
        glColor3f(0,0,1);
        glVertex3fv(axisVerts[0]);
        glVertex3fv(axisVerts[3]);
    glEnd();
}

void draw3DObject(Object3D obj){
    for(int i = 0; i < obj.nfaces; ++i)
    {
        Face3D f;

        f.x = obj.faces[i].x;
        f.y = obj.faces[i].y;
        f.z = obj.faces[i].z;

        glBegin(GL_TRIANGLES);
            glVertex3fv(obj.vertices[f.x]);
            glVertex3fv(obj.vertices[f.y]);
            glVertex3fv(obj.vertices[f.z]);

        glEnd();
    }
        //translateObject3D(&obj, &centerOfMass); //moves object to 0,0,0
}


void keys(unsigned char key, int x, int y) /// moving the camera
{
    if(key == 'x'){
        viewer[0] -= 1;
    }
    if(key == 'X'){
            viewer[0] += 1;
    }
    if(key == 'y') viewer[1] -= 1;
    if(key == 'Y') viewer[1] += 1;
    if(key == 'z') viewer[2] -= 1;
    if(key == 'Z') viewer[2] += 1;

    if(key == 'q' || key == 'Q') exit(0);

    glutPostRedisplay();
}



void display(void){
 /* declare a point data type */
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();

 gluLookAt(viewer[0], viewer[1], viewer[2],
           viewer[3], viewer[4], viewer[5],
           viewer[6], viewer[7], viewer[8]);

  drawAxis();

    drawCourt();
    currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    timeSincePrevFrame = currTime - prevTime;
    //glutTimerFunc(TIMER,movePlayerA, 0); // this function is called every TIMER ms
   // glutTimerFunc(TIMER,movePlayerB, 0); // this function is called every TIMER ms
    movePlayerB();
    movePlayerA();
    prevTime = currTime;

    glutPostRedisplay(); /// redisplay called only after both player positions updated
///----------------------( drawing first character ) ------------------
    glPushMatrix();
    /// height and adding it to the Y as otherwise character is halfway into the ground
    playerColours[0][0] = 1.0; // 0 to access colour profile for first character, then 0 to access Red float value
    playerColours[0][1] = 0.0;
    playerColours[0][2] = 0.0;
    glTranslatef(65.0, 2.0 * playerArray[0].charHieght , -10.0); /// starting location of player1
    glRotatef(90.0,0.0,1.0,0.0); /// two players start facing each other
    drawPlayer(0, playerColours[0]);          // passing index for player1, first element of player array and Array of a 3 element RGB array
    drawRacket(0);

    glPopMatrix();
///----------------------( drawing second character ) ----------
    glPushMatrix();

    playerColours[1][0] = 0.0;
    playerColours[1][1] = 1.0;
    playerColours[1][2] = 0.0;
    glTranslatef(65.0, 2.0 * playerArray[1].charHieght , -55.0); /// starting location of player2
    glRotatef(90.0,0.0,1.0,0.0);
    drawPlayer(1, playerColours[1]); // passing index for player1, second element of player array
    drawRacket(1);

    glPopMatrix();
//-------------------------------------------------------------

 glFlush(); /* flush buffers */
}

void read3DObjects()
{
        //changing to read in data into all playerObjects from an array
    for(int i = 0; i < 2; i++){
        ReadOFFfile("objects/Capsule.off", &playerArray[i].charObj);
        ReadOFFfile("objects/Racket_Handle.off", &playerArray[i].handle);
        ReadOFFfile("objects/Racket_Pad.off", &playerArray[i].pad);

        calcCenterOfMass(playerArray[i].charObj, playerArray[i].CoM ); /// added this each players COM
        getMaxMin(playerArray[i].charObj, ma1, mi1); /// so far only used this so I can get the players height
        playerArray[i].charHieght = maxYFloat - minYFloat;

    }
}

void idle(){    glutPostRedisplay();}

int main(int argc, char** argv) {
    read3DObjects();

    glutInit(&argc,argv); /* Standard GLUT initialization */

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB  | GLUT_DEPTH); //(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600); /* 500 x 500 pixel window */
    glutInitWindowPosition(0,0); /* place window top left on display */
    glutCreateWindow("Squash Simulator"); /* window title */

    myinit(); /* set attributes */
    glutDisplayFunc(display); /* display callback invoked when window is opened */

    //glutSpecialUpFunc(movePlayerA);
    glutSpecialFunc(pressedSpecialDown); /// this function for arrow key movement
    glutSpecialUpFunc(pressedSpecialUp);
    glutKeyboardFunc(pressedDown);     /// this function for WASD movement, camera doesn't need to be manipulated by key press, camera can move by itself relative to the position of the ball maybe
    glutKeyboardUpFunc(pressedUp);

     prevTime = glutGet(GLUT_ELAPSED_TIME) / 1000.f;

    glutMainLoop(); /* enter event loop */

 return 0;
}
