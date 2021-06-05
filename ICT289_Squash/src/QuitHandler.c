#include "../include/QuitHandler.h"

#include "TextureLoader.h"

GLuint texID;
void LoadImages(){

    texID = LoadTexture("textures/GroupPic.raw", 946, 437, 4);
}

void DrawGroupCred(){

        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texID);
            glRotatef(190,0,0,1);
            glScalef(5,5,5);
            glTranslatef(0,-30,25);
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

