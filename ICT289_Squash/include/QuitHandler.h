#ifndef QUITHANDLER_H
#define QUITHANDLER_H

//#include "TextureLoader.h"
#ifdef _WIN32
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif

    ///Hold read/loaded image
GLuint texID;

    //load image (hard coded)
void LoadImages();

    //Displays image stored in texID
void DrawGroupCred();

#endif // QUITHANDLER_H
