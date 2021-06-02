#ifndef QUITHANDLER_H
#define QUITHANDLER_H

#include "TextureLoader.h"

GLuint texID;
void LoadImages()
{
        ///OUR group pic
    //texSplashScreen = LoadTexture("res/GroupPic.raw", 946, 437, 4);
    texID = LoadTexture("textures/GroupPic.raw", 946, 437, 4);

}

void DrawGroupCred()
{
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH); // Window Width
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT); // Window Height
    //printf("W: %d , H: %d", windowWidth, windowHeight);
    //glMatrixMode(GL_PROJECTION);
    //glPushMatrix();
        //glLoadIdentity();
        //glOrtho(0, windowWidth, windowHeight, 0, 0.1, 100);

        //glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            //glLoadIdentity();
            glBindTexture(GL_TEXTURE_2D, texID);
            //glColor3f(0,1,0);
            glRotatef(180,0,0,1);
            //glRotatef(180,0,1,0);
            glScalef(5,5,5);
            glTranslatef(0,-25,25);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0);
                glVertex3f(10,8, -10);

                glTexCoord2f(0.0, 1.0);
                glVertex3f(10,50, -10);

                glTexCoord2f(1.0, 1.0);
                glVertex3f(10,50, -55);

                glTexCoord2f(1.0, 0.0);
                glVertex3f(10,8, -55);
            glEnd();
        glPopMatrix();
}

#endif // QUITHANDLER_H
