
#include "Geometry.h"

void drawCourt(){

    Point3D leftWall[4] = { {0.0,0.0,0.0},  {0.0, 56.4, 0.0}, {0.0,56.4,-64.0}, {0.0, 0.0, -64.0} };
    Point3D serviceLine[2] = { {0.0, 5.0, 0.0}, {0.0,5.0, -64.0} };
    Point3D frontWallLine[4] = { {0.0, 45.7, 0.0}, {0.0, 17.8, 0.0},  {0.0, 17.8, -64.0} , {0.0, 45.7, -64.0}  };
    Point3D HCL[2] = { {54.4,0.1,-64.0/2.0}, {54.4+42.1,0.1,-64.0/2.0 }   };
    Point3D shortLine[2] = {  {54.4,0.1,0.0}, {54.4, 0.1, -64.0}  };
    Point3D SB1[4]  = {  {54.4, 0.1, 0.0}, {54.4 + 16.0, 0.1, 0.0}, {54.4 + 16.0, 0.1, -64.0/4.0}, {54.4, 0.1, -64.0/4}   };
    Point3D SB2[4] = { {54.4, 0.1, -64.0}, {54.4 + 16.0, 0.1, -64.0}, {54.4 + 16.0, 0.1, -3*(64.0/4.0)},
        {54.4, 0.1, -3*(64.0/4.0)} };
    Point3D backWallLine[2] = { {54.4 + 16.0 + 26.1, 21.3, 0.0}, {54.4 + 16.0 + 26.1, 21.3, -64.0}  };

    Point3D backWall[4] = {  {54.4 + 16.0 + 26.1, 0.0, 0.0} , {54.4 + 16.0 + 26.1, 0.0, -64.0},
        {54.4 + 16.0 + 26.1, 56.0, -64.0}, {54.4 + 16.0 + 26.1, 56.0, 0.0}       };
    Point3D sideWall[4] = { {0.0,0.0,-64.0}, {0.0,56.4,-64.0}, {54.4 + 16.0 + 26.1 ,56.4,-64.0},
        {54.4 + 16.0 + 26.1 ,0.0,-64.0}
    };
    Point3D sideWallLine[2] = { {0.0, 45.7, -64.0}, {54.4 + 16.0 + 26.1, 21.3, -64.0}  };
    Point3D frontWall[4] = { {0.0,0.0,0.0}, {0.0,56.4,0.0}, {54.4 + 16.0 + 26.1 ,56.4,0.0},
        {54.4 + 16.0 + 26.1 ,0.0,0.0} };
    Point3D roof[4] = { {0.0,56.4,0.0}, {0.0,56.4,-64.0}, {54.4 + 16.0 + 26.1, 56.4, -64.0}, {54.4 + 16.0 + 26.1, 56.4, 0.0}   };
    Point3D floor[4] = { {0.0,0.0,0.0}, {0.0,0.0,-64.0}, {54.4 + 16.0 + 26.1, 0.0, -64.0}, {54.4 + 16.0 + 26.1, 0.0, 0.0}   };

    glBegin(GL_LINE_LOOP);

        glColor3f(0.0,0.0,0.0);
        glVertex3fv(leftWall[0]);
        glVertex3fv(leftWall[1]);
        glVertex3fv(leftWall[2]);
        glVertex3fv(leftWall[3]);

    glEnd();

    glBegin(GL_LINE_LOOP);

        glColor3f(1.0,0.0,0.0);
        glVertex3fv(serviceLine[0]);
        glVertex3fv(serviceLine[1]);

    glEnd();

    glBegin(GL_LINE_LOOP);

        glColor3f(0.0,0.0,0.0);
        glVertex3fv(frontWallLine[0]);
        glVertex3fv(frontWallLine[1]);
        glVertex3fv(frontWallLine[2]);
        glVertex3fv(frontWallLine[3]);

    glEnd();

    glBegin(GL_LINE_LOOP);

        glColor3f(1.0,0.0,0.0);
        glVertex3fv(HCL[0]);
        glVertex3fv(HCL[1]);

    glEnd();

    glBegin(GL_LINE_LOOP);

        glColor3f(1.0,0.0,0.0);
        glVertex3fv(shortLine[0]);
        glVertex3fv(shortLine[1]);

    glEnd();

    glBegin(GL_LINE_LOOP);

        glColor3f(1.0,0.0,0.0);
        glVertex3fv(SB1[0]);
        glVertex3fv(SB1[1]);
        glVertex3fv(SB1[2]);
        glVertex3fv(SB1[3]);

    glEnd();

    glBegin(GL_LINE_LOOP);

        glColor3f(1.0,0.0,0.0);
        glVertex3fv(SB2[0]);
        glVertex3fv(SB2[1]);
        glVertex3fv(SB2[2]);
        glVertex3fv(SB2[3]);

    glEnd();
    glBegin(GL_LINE_LOOP);

        glColor3f(0.0,0.0,0.0);
        glVertex3fv(backWallLine[0]);
        glVertex3fv(backWallLine[1]);

    glEnd();

    glBegin(GL_LINE_LOOP);

        glColor3f(0.0,0.0,0.0);
        glVertex3fv(backWall[0]);
        glVertex3fv(backWall[1]);
        glVertex3fv(backWall[2]);
        glVertex3fv(backWall[3]);

    glEnd();

    glBegin(GL_LINE_LOOP);

        glColor3f(0.0,0.0,0.0);
        glVertex3fv(sideWall[0]);
        glVertex3fv(sideWall[1]);
        glVertex3fv(sideWall[2]);
        glVertex3fv(sideWall[3]);

    glEnd();

    glBegin(GL_LINE_LOOP);

        glColor3f(0.0,0.0,0.0);
        glVertex3fv(sideWallLine[0]);
        glVertex3fv(sideWallLine[1]);

    glEnd();

    glBegin(GL_LINE_LOOP);

        glColor3f(0.0,0.0,0.0);
        glVertex3fv(frontWall[0]);
        glVertex3fv(frontWall[1]);
        glVertex3fv(frontWall[2]);
        glVertex3fv(frontWall[3]);

    glEnd();

    /*
    glBegin(GL_POLYGON);

        glColor3f(0.3,0.3,0.3);
        glVertex3fv(roof[0]);
        glVertex3fv(roof[1]);
        glVertex3fv(roof[2]);
        glVertex3fv(roof[3]);

    glEnd();*/

    glBegin(GL_POLYGON);

        glColor3f(1,0.7,0.0);
        glVertex3fv(floor[0]);
        glVertex3fv(floor[1]);
        glVertex3fv(floor[2]);
        glVertex3fv(floor[3]);

    glEnd();


}


