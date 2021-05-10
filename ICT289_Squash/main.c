#include <stdio.h>
#include <stdlib.h>

#include "include/Geometry.h"
#include "include/ReadOFFfile.h"
#include "include/player.h"
#include "include/Room.h"
#include "include/collisionDetectionAABB.h"

#include <GL/freeglut.h>
#include <GL/glut.h>

static GLdouble viewer[]= {50.0, 10.0, 80.0, // initial camera location (across, up/down, distance to object)
                           0.0, 0.0, 0.0, // initial look at point
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


void keys(unsigned char key, int x, int y)
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
        //Draw player (Capsule)

    glColor3f(0.4, 0.1, 0.1);
    glScaled(0.02,0.02,0.02);
    draw3DObject(playerA.charObj);
        //Draw racket
    glColor3f(0.6, 0.2, 0.2);
    draw3DObject(playerA.handle);
    glColor3f(0.7,0.7,0.7);
    draw3DObject(playerA.pad);

 glFlush(); /* flush buffers */
}

void read3DObjects()
{
        //Read all objects for player ONE
    ReadOFFfile("objects/Capsule.off", &playerA.charObj);
    ReadOFFfile("objects/Racket_Handle.off", &playerA.handle);
    ReadOFFfile("objects/Racket_Pad.off", &playerA.pad);
}

int main(int argc, char** argv) {
    read3DObjects();

    glutInit(&argc,argv); /* Standard GLUT initialization */

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB  | GLUT_DEPTH); //(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600); /* 500 x 500 pixel window */
    glutInitWindowPosition(0,0); /* place window top left on display */
    glutCreateWindow("Draw complex 3D object"); /* window title */

    myinit(); /* set attributes */
    glutDisplayFunc(display); /* display callback invoked when window is opened */

    glutSpecialFunc(movePlayerA);
    glutKeyboardFunc(keys);
    glutMainLoop(); /* enter event loop */

 return 0;
}
