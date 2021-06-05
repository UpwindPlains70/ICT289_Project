#ifndef ROOM_H
#define ROOM_H

#include "Geometry.h"

const Point3D frontWall[4] = { {0.0,0.0,0.0},  {0.0, 56.4, 0.0}, {0.0,56.4,-64.0}, {0.0, 0.0, -64.0} };
const Point3D serviceLine[2] = { {0.0, 5.0, 0.0}, {0.0,5.0, -64.0} };
const Point3D frontWallLine[4] = { {0.0, 45.7, 0.0}, {0.0, 17.8, 0.0},  {0.0, 17.8, -64.0} , {0.0, 45.7, -64.0}  };
const Point3D HCL[2] = { {54.4,0.1,-64.0/2.0}, {54.4+42.1,0.1,-64.0/2.0 }   };
const Point3D shortLine[2] = {  {54.4,0.1,0.0}, {54.4, 0.1, -64.0}  };
const Point3D SB1[4]  = {  {54.4, 0.1, 0.0}, {54.4 + 16.0, 0.1, 0.0}, {54.4 + 16.0, 0.1, -64.0/4.0}, {54.4, 0.1, -64.0/4}   };
const Point3D SB2[4] = { {54.4, 0.1, -64.0}, {54.4 + 16.0, 0.1, -64.0}, {54.4 + 16.0, 0.1, -3*(64.0/4.0)},
                        {54.4, 0.1, -3*(64.0/4.0)} };
const Point3D backWallLine[2] = { {54.4 + 16.0 + 26.1, 21.3, 0.0}, {54.4 + 16.0 + 26.1, 21.3, -64.0}  };

const Point3D backWall[4] = {  {54.4 + 16.0 + 26.1, 0.0, 0.0} , {54.4 + 16.0 + 26.1, 0.0, -64.0},
                            {54.4 + 16.0 + 26.1, 56.0, -64.0}, {54.4 + 16.0 + 26.1, 56.0, 0.0}       };
const Point3D rightWall[4] = { {0.0,0.0,-64.0}, {0.0,56.4,-64.0}, {54.4 + 16.0 + 26.1 ,56.4,-64.0},
                            {54.4 + 16.0 + 26.1 ,0.0,-64.0}};
const Point3D rightSideWallLine[2] = { {0.0, 45.7, -64.0}, {54.4 + 16.0 + 26.1, 21.3, -64.0}  };
const Point3D leftSideWallLine[2] = { {0.0, 45.7, 0.0}, {54.4 + 16.0 + 26.1, 21.3, 0.0}  };
const Point3D leftWall[4] = { {0.0,0.0,0.0}, {0.0,56.4,0.0}, {54.4 + 16.0 + 26.1 ,56.4,0.0},
                                {54.4 + 16.0 + 26.1 ,0.0,0.0} };
const Point3D roof[4] = { {0.0,56.4,0.0}, {0.0,56.4,-64.0}, {54.4 + 16.0 + 26.1, 56.4, -64.0}, {54.4 + 16.0 + 26.1, 56.4, 0.0}   };
const Point3D gamefloor[4] = { {0.0,0.0,0.0}, {0.0,0.0,-64.0}, {54.4 + 16.0 + 26.1, 0.0, -64.0}, {54.4 + 16.0 + 26.1, 0.0, 0.0}   };

const GLfloat wallColor[] = {1, 1, 1}; //White
const GLfloat outLineColor[] = {0, 0, 0}; //Black
const GLfloat serviceLineColor[] = {1, 0, 0}; //Red
const GLfloat roofColor[] = {0.3, 0.3, 0.3}; //Grey
const GLfloat floorColor[] = {1, 0.7, 0.0}; //Orange

void drawCourt(){

            ///Front wall
    glBegin(GL_POLYGON);

        glColor3fv(wallColor);
        glVertex3fv(frontWall[0]);
        glVertex3fv(frontWall[1]);
        glVertex3fv(frontWall[2]);
        glVertex3fv(frontWall[3]);

    glEnd();

            ///Red serv line (back wall)
    glBegin(GL_LINE_LOOP);

        glColor3fv(serviceLineColor);
        glVertex3fv(serviceLine[0]);
        glVertex3fv(serviceLine[1]);

    glEnd();

            ///Back lines (mid wall)
    glBegin(GL_LINE_LOOP);

        glColor3fv(outLineColor);
        glVertex3fv(frontWallLine[0]);
        glVertex3fv(frontWallLine[1]);
        glVertex3fv(frontWallLine[2]);
        glVertex3fv(frontWallLine[3]);

    glEnd();

            ///Player section line (mid play zone)
    glBegin(GL_LINE_LOOP);

        glColor3fv(serviceLineColor);
        glVertex3fv(HCL[0]);
        glVertex3fv(HCL[1]);

    glEnd();
            ///Front service line
    glBegin(GL_LINE_LOOP);

        glColor3fv(serviceLineColor);
        glVertex3fv(shortLine[0]);
        glVertex3fv(shortLine[1]);

    glEnd();
            ///P1 Service square
    glBegin(GL_LINE_LOOP);

        glColor3fv(serviceLineColor);
        glVertex3fv(SB1[0]);
        glVertex3fv(SB1[1]);
        glVertex3fv(SB1[2]);
        glVertex3fv(SB1[3]);

    glEnd();

            ///P2 Service square
    glBegin(GL_LINE_LOOP);

        glColor3fv(serviceLineColor);
        glVertex3fv(SB2[0]);
        glVertex3fv(SB2[1]);
        glVertex3fv(SB2[2]);
        glVertex3fv(SB2[3]);

    glEnd();

    glBegin(GL_LINE_LOOP);

        glColor3fv(outLineColor);
        glVertex3fv(backWallLine[0]);
        glVertex3fv(backWallLine[1]);

    glEnd();

            ///Front wall (camera loc)
    glBegin(GL_LINE_LOOP);

        glColor3fv(outLineColor);
        glVertex3fv(backWall[0]);
        glVertex3fv(backWall[1]);
        glVertex3fv(backWall[2]);
        glVertex3fv(backWall[3]);

    glEnd();

            ///Right wall
    glBegin(GL_POLYGON);

        glColor3fv(wallColor);
        glVertex3fv(rightWall[0]);
        glVertex3fv(rightWall[1]);
        glVertex3fv(rightWall[2]);
        glVertex3fv(rightWall[3]);

    glEnd();

            ///left side line
    glBegin(GL_LINE_LOOP);

        glColor3fv(outLineColor);
        glVertex3fv(leftSideWallLine[0]);
        glVertex3fv(leftSideWallLine[1]);

    glEnd();

            ///right side line
    glBegin(GL_LINE_LOOP);

        glColor3fv(outLineColor);
        glVertex3fv(rightSideWallLine[0]);
        glVertex3fv(rightSideWallLine[1]);

    glEnd();

            ///Left wall
    glBegin(GL_POLYGON);

        glColor3fv(wallColor);
        glVertex3fv(leftWall[0]);
        glVertex3fv(leftWall[1]);
        glVertex3fv(leftWall[2]);
        glVertex3fv(leftWall[3]);

    glEnd();


    glBegin(GL_POLYGON);

        glColor3fv(roofColor);
        glVertex3fv(roof[0]);
        glVertex3fv(roof[1]);
        glVertex3fv(roof[2]);
        glVertex3fv(roof[3]);

    glEnd();

            ///Floor
    glBegin(GL_POLYGON);

        glColor3fv(floorColor);
        glVertex3fv(gamefloor[0]);
        glVertex3fv(gamefloor[1]);
        glVertex3fv(gamefloor[2]);
        glVertex3fv(gamefloor[3]);

    glEnd();

}

#endif //ROOM_H

