#include "UI.h"

struct Texture texSplashScreen;
void InitializeUI()
{
        ///OUR group pic
    texSplashScreen = LoadTexture("res/GroupPic.raw", 946, 437, 4);

        ///Original groups pic
    //texSplashScreen = LoadTexture("res/SplashScreen.raw", 1024, 512, 4);
}

void DrawSplash()
{
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH); // Window Width
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT); // Window Height
    glMatrixMode(GL_PROJECTION);
    //glPushMatrix();
        glLoadIdentity();
        glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        //glPushMatrix();
            glLoadIdentity();
            glBindTexture(GL_TEXTURE_2D, texSplashScreen.texId);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(0, 0, 0);
                glTexCoord2f(0, 1);
                glVertex3f(0, windowHeight, 0);
                glTexCoord2f(1, 1);
                glVertex3f(windowWidth, windowHeight, 0);
                glTexCoord2f(1, 0);
                glVertex3f(windowWidth, 0, 0);
            glEnd();
        //glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    //glPopMatrix();
}
