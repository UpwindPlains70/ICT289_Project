#include "../include/TextureLoader.h"

#include <stdio.h>

GLuint LoadTexture(const char * filepath, int width, int height, int byteSize)
{
    unsigned char * data;
    FILE * filePointer;
    filePointer = fopen(filepath, "rb");
    if(filePointer == NULL)
    {
        printf("Error loading texture: %s\n", filepath);
        return;
    }

    int fileSize = width * height * byteSize;
    data = (unsigned char *)malloc(fileSize);
    fread(data, fileSize, 1, filePointer);
    fclose(filePointer);

    GLuint texId = 0;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

	free(data);

	return texId;
}
