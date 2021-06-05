#ifndef QUITHANDLER_H
#define QUITHANDLER_H

//#include "TextureLoader.h"
#ifdef _WIN32
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif

GLuint texID;
void LoadImages();

void DrawGroupCred();

#endif // QUITHANDLER_H
