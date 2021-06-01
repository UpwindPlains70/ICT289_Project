#ifndef READOFFfile_H
#define READOFFfile_H

#include <stdio.h>
#include <stdlib.h>
#include "Geometry.h"

void ReadOFFfile(char* fileName, Object3D *newObject);

void PointReader(Object3D *obj, FILE *in_File);
void FaceReader(Object3D *obj, FILE *in_File);


char title[];//junk bin for first line of file

//Reads an OFF storing data in passed Object3D
//Pre-condition: Existing file name and Object3D variable
//Post-condition: populates the passed Object3D
void ReadOFFfile(char* fileName, Object3D *newObject){

    int bufferLength = 255;
    int trash;

    FILE *in_file = fopen(fileName, "r");

    //test for existing file
    if(in_file == NULL)
    {
        printf("Error! Could not open file: %s\n", fileName);
        exit(-1);
    }

    //first line is title (OFF)
    fgets(title, bufferLength, in_file);
    //Total points are first in line 2
    fscanf (in_file, "%d", &newObject->nverts);
    //total vectors are second in line 2
    fscanf (in_file, "%d", &newObject->nfaces);
    //line 2 has another value of 0
    fscanf (in_file, "%d", &trash);

    PointReader(newObject, in_file);
    FaceReader(newObject, in_file);

    fclose(in_file);
}

//Read vertices from OFF file
//Pre-condition: OFF file must be read
//Post-condition: all vertices stored in object3D
void PointReader(Object3D *obj, FILE *in_file){

    obj->vertices = (Point3D*)malloc(obj->nverts * sizeof(Point3D));
    for(int i = 0; i < obj->nverts; i++) {
        fscanf (in_file, "%f", &obj->vertices[i][0]);
        fscanf (in_file, "%f", &obj->vertices[i][1]);
        fscanf (in_file, "%f", &obj->vertices[i][2]);
    }
}

//Read faces from OFF file
//Pre-condition: OFF file must be read
//Post-condition: all faces stored in object3D
void FaceReader(Object3D *obj, FILE *in_file){
int trash;

    obj->faces = (Face3D*)malloc(obj->nfaces * sizeof(Face3D));
    for(int i = 0; i < obj->nfaces; i++) {
        fscanf (in_file, "%d", &trash);//Scrap read that indicates the face is a triangle
        fscanf (in_file, "%d", &obj->faces[i].x);
        fscanf (in_file, "%d", &obj->faces[i].y);
        fscanf (in_file, "%d", &obj->faces[i].z);

    }
}

#endif //READOFFfile_H
