#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <math.h>
#include <GL/freeglut.h>
#include <GL/glut.h>

typedef GLfloat Point3D[3];

typedef struct Face3D{
    int x,y,z;
}Face3D;

typedef struct Object3D{
    int nverts, nfaces;
    Point3D *vertices;
    Face3D *faces;
}Object3D;

//Scales a vector by a given number
//Pre-Condition: valid vector and scale number required
//Post-Condition: Returns a vector that has been scaled
void Scale3DPoint(Point3D *pnt, float scale)
{
    *pnt[0] *= scale;
    *pnt[1] *= scale;
    *pnt[2] *= scale;

}

//Scales a 3D object by a given number
//Pre-Condition: valid 3DObject and scale number required
//Post-Condition: Returns a 3DObject that has been scaled
void Scale3DObject(Object3D *obj, float scale)
{
    for(int i = 0; i < obj->nverts; i++)
    {
        Scale3DPoint(&obj->vertices[i], scale);
    }

   // return obj;
}

//Calculates the dot product of two vectors
//Pre-Condition: requires two valid Face3D objects as input
//Post-condition: returns the dot product as a float
float DotProduct(Face3D v1, Face3D v2)
{
    return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

//Calculates the cross product of two vectors
//Pre-Condition: requires two valid Face3D objects as input
//Post-condition: returns the cross product as a new Face3D
Face3D CrossProduct(Face3D v1, Face3D v2)
{
    Face3D newVector;

    newVector.x = (v1.y * v2.z) - (v1.z * v2.y);
    newVector.y = (v1.z * v2.x) - (v1.x * v2.z);
    newVector.z = (v1.x * v2.y) - (v1.y * v2.x);

    return newVector;
}

//Calculates the Normal Vector to a triangle
//Pre-Condition: requires two valid Face3D objects as input
//Post-condition: returns the cross product as a new Face3D (cross product = normal vector)
Face3D NormalVector(Face3D v1, Face3D v2)
{
    return CrossProduct(v1, v2);
}

//Magnitude
double calcNormalLength(Face3D vec)
{
        return sqrt((vec.x^2) + (vec.y^2) + (vec.z^2));
}


void translateToOrogin(Object3D *obj, Point3D CoM)
{
    for(int i = 0; i < obj->nverts; i++)
    {
        obj->vertices[i][0] -= CoM[0];
        obj->vertices[i][1] -= CoM[1];
        obj->vertices[i][2] -= CoM[2];
    }
}

void translate3DObject(Object3D *obj, GLfloat x, GLfloat y, GLfloat z)
{
    for(int i = 0; i < obj->nverts; i++)
    {
        obj->vertices[i][0] += x;
        obj->vertices[i][1] += y;
        obj->vertices[i][2] += z;
    }
}


float calcRadius(Object3D *obj, GLfloat *CoM)
{
    float maxLength = 0;
    float tmpLength = 0;
    for(int i = 0; i < obj->nfaces; i++)
    {
        tmpLength = (obj->faces[i].x - CoM[0]) - (obj->faces[i].y - CoM[1]) - (obj->faces[i].z - CoM[2]);
        if(tmpLength > maxLength)
        {
            maxLength = tmpLength;
        }
    }
    return maxLength;
}

//Calculate center of mass of given object
//Pre-conditions: Valid existing object3D and address to a Poin3D
//Post-conditions: populates passed Poin3D with center of mass
void calcCenterOfMass(Object3D obj, Point3D *CoM){
    *CoM[0] = 0; //Set to zero for accurate calculations
    *CoM[1] = 0; //Set to zero for accurate calculations
    *CoM[2] = 0; //Set to zero for accurate calculations

    for(int i = 0; i < obj.nverts; ++i)
    {
        *CoM[0] += obj.vertices[i][0];
        *CoM[1] += obj.vertices[i][1];
        *CoM[2] += obj.vertices[i][2];
    }

    *CoM[0] /= obj.nverts;
    *CoM[1] /= obj.nverts;
    *CoM[2] /= obj.nverts;
}

Face3D UnitNormalVector(Face3D v1, Face3D v2)
{
    Face3D normalVec = NormalVector(v1, v2);

    double length = calcNormalLength(normalVec);

    normalVec.x = normalVec.x/length;
    normalVec.y = normalVec.y/length;
    normalVec.z = normalVec.z/length;

    return normalVec;
}

void pointCopy(Point3D source, Point3D *dest)
{
    *dest[0] = source[0];
    *dest[1] = source[1];
    *dest[2] = source[2];
}

//Calculate area of triangle
//Pre-Condition: requires two valid Face3D objects as input
//Post-condition: returns the area as a float
float AreaOfTriangle(Face3D v1, Face3D v2)
{
    Face3D tmpVector = CrossProduct(v1, v2);

    //float ParallelogramArea = sqrt(tmpVector.x^2 + tmpVector.y^2 + tmpVector.z^2);

    return calcNormalLength(tmpVector)/2;
}
#endif // GEOMETRY_H

