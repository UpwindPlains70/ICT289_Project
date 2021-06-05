#ifndef READOFFfile_H
#define READOFFfile_H
#include <stdio.h>
#include <stdlib.h>
#include "Geometry.h"

char title[];//junk bin for first line of file

//Reads an OFF storing data in passed Object3D
//Pre-condition: Existing file name and Object3D variable
//Post-condition: populates the passed Object3D
void ReadOFFfile(char* fileName, Object3D *newObject);

//Read vertices from OFF file
//Pre-condition: OFF file must be read
//Post-condition: all vertices stored in object3D
void PointReader(Object3D *obj, FILE *in_file);

//Read faces from OFF file
//Pre-condition: OFF file must be read
//Post-condition: all faces stored in object3D
void FaceReader(Object3D *obj, FILE *in_file);

//Calc direction of faces (UP vector)
void NormReader(Object3D *obj);
#endif //READOFFfile_H
