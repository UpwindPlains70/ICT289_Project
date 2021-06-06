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
    Point3D *norms;
    Point3D *vertices;
    Face3D *faces;
}Object3D;


//Scales a vector by a given number
//Pre-Condition: valid vector and scale number required
//Post-Condition: Returns a vector that has been scaled
void Scale3DPoint(Point3D *pnt, float scale);

//Scales a 3D object by a given number
//Pre-Condition: valid 3DObject and scale number required
//Post-Condition: Returns a 3DObject that has been scaled
void Scale3DObject(Object3D *obj, float scale);

void calcVector(Point3D p1, Point3D p2, Point3D destination);

//Calculates the dot product of two vectors
//Pre-Condition: requires two valid Face3D objects as input
//Post-condition: returns the dot product as a float
double DotProduct(Point3D v1, Point3D v2);

//Calculates the cross product of two vectors
//Pre-Condition: requires two valid Face3D objects as input
//Post-condition: returns the cross product as a new Face3D
void CrossProduct(Point3D v1, Point3D v2, Point3D destination);

//Calculates the Normal Vector to a triangle
//Pre-Condition: requires two valid Face3D objects as input
//Post-condition: returns the cross product as a new Face3D (cross product = normal vector)
void NormalVector(Point3D v1, Point3D v2, Point3D destination);

//Magnitude
double calcNormalLength(Point3D vec);

//Move object to 0,0,0 by taking the centre of mass from the object
void translateToOrogin(Object3D *obj, Point3D CoM);

//Calc max radius of an object
float calcRadius(Object3D *obj, GLfloat *CoM);

//Calculate center of mass of given object
//Pre-conditions: Valid existing object3D and address to a Poin3D
//Post-conditions: populates passed Poin3D with center of mass
void calcCenterOfMass(Object3D obj, Point3D CoM);

//Calculate unit normal vector of 3 points
void UnitNormalVector(Point3D v1, Point3D v2, Point3D v3, Point3D destination);

void calcUnitNormalVector(Point3D v1, Point3D v2, Point3D destination);

//Allow for a deep copy of a Point3D
void pointCopy(Point3D source, Point3D *dest);

//Calc the distance from a sphere to a given plane
double distanceFromSphereToPlane(Point3D sphereCoM, Point3D planeP1, Point3D planeP2, Point3D planeP3);

//Draw object using GLUT
void draw3DObject(Object3D obj);

#endif // GEOMETRY_H

