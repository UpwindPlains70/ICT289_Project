#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

//#include <stdio.h>
#ifdef _WIN32
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif

GLuint LoadTexture(const char * filepath, int width, int height, int byteSize);

#endif // TEXTURELOADER_H
