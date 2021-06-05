#include "Geometry.h"


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

void calcVector(Point3D p1, Point3D p2, Point3D destination)
{
    destination[0] = p1[0] - p2[0];
    destination[1] = p1[1] - p2[1];
    destination[2] = p1[2] - p2[2];
}

//Calculates the dot product of two vectors
//Pre-Condition: requires two valid Face3D objects as input
//Post-condition: returns the dot product as a float
double DotProduct(Point3D v1, Point3D v2)
{
    return ((v1[0] * v2[0]) + (v1[1] * v2[1]) + (v1[2] * v2[2]));
}

//Calculates the cross product of two vectors
//Pre-Condition: requires two valid Face3D objects as input
//Post-condition: returns the cross product as a new Face3D
void CrossProduct(Point3D v1, Point3D v2, Point3D destination)
{
    destination[0] = ((v2[1] * v1[2]) - (v2[2] * v1[1]));
    destination[1] = ((v2[2] * v1[0]) - (v2[0] * v1[2]));
    destination[2] = ((v2[0] * v1[1]) - (v2[1] * v1[0]));
}

//Calculates the Normal Vector to a triangle
//Pre-Condition: requires two valid Face3D objects as input
//Post-condition: returns the cross product as a new Face3D (cross product = normal vector)
void NormalVector(Point3D v1, Point3D v2, Point3D destination)
{
    CrossProduct(v1, v2, destination);
}

//Magnitude
double calcNormalLength(Point3D vec)
{
    return sqrt((vec[0]*vec[0]) + (vec[1]*vec[1]) + (vec[2]*vec[2]));
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
void calcCenterOfMass(Object3D obj, Point3D CoM){ /// changed from Point3D *CoM as I couldn't get it working
    CoM[0] = 0.0; //Set to zero for accurate calculations
    CoM[1] = 0.0; //Set to zero for accurate calculations
    CoM[2] = 0.0; //Set to zero for accurate calculations

    for(int i = 0; i < obj.nverts; ++i)
    {
        CoM[0] += obj.vertices[i][0];
        CoM[1] += obj.vertices[i][1];
        CoM[2] += obj.vertices[i][2];
    }

    CoM[0] /= obj.nverts;
    CoM[1] /= obj.nverts;
    CoM[2] /= obj.nverts;

    //printf("%d %d %d\n", CoM[0], CoM[1], CoM[2]);
}

void calcUnitNormalVector(Point3D v1, Point3D v2, Point3D destination)
{
    //Point3D unitNormVec = {0,0,0};
    Point3D normVec;
    NormalVector(v1, v2, normVec);

    float normLength = calcNormalLength(normVec);

    destination[0] = normVec[0] / normLength;
    destination[1] = normVec[1] / normLength;
    destination[2] = normVec[2] / normLength;

   //return unitNormVec;
}

void pointCopy(Point3D source, Point3D *dest)
{
    *dest[0] = source[0];
    *dest[1] = source[1];
    *dest[2] = source[2];
}

double distanceFromSphereToPlane(Point3D sphereCoM, Point3D planeP1, Point3D planeP2, Point3D planeP3)
{
    Point3D vectorOfSpherToPlane;
    calcVector(sphereCoM, planeP1, vectorOfSpherToPlane);

    Point3D unitNormalVector;
    calcUnitNormalVector(planeP1, planeP2, unitNormalVector);
    return fabs(DotProduct(vectorOfSpherToPlane, unitNormalVector));
}

void draw3DObject(Object3D obj){
    for(int i = 0; i < obj.nfaces; ++i)
    {
        Face3D f;

        f.x = obj.faces[i].x;
        f.y = obj.faces[i].y;
        f.z = obj.faces[i].z;

        glBegin(GL_TRIANGLES);
            glNormal3fv(obj.norms[i]);
            glVertex3fv(obj.vertices[f.x]);
            glVertex3fv(obj.vertices[f.y]);
            glVertex3fv(obj.vertices[f.z]);
        glEnd();
    }
}

