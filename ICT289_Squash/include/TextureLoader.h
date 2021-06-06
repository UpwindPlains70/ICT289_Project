#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

//#include <stdio.h>
#ifdef _WIN32
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif

    ///Load a .raw image into GLUT image store
    //Requires image width, height, and 4
GLuint LoadTexture(const char * filepath, int width, int height, int byteSize);

#endif // TEXTURELOADER_H
