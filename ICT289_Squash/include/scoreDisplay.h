#ifndef SCOREDISPLAY_H_INCLUDED
#define SCOREDISPLAY_H_INCLUDED

///Due to the nature of this code, scores are of a maximum of 9 as any further will lead to ascill code beyond 9;

//change values on top to alter score;
int plyr1 = 0;
int plyr2 = 0;

void WriteCaptions(void)
{
    //int to character
    char p1 = plyr1+'0';
    char p2 = plyr2+'0';

    //colour
    glColor3f(0.0, 0.0, 0.0);

    //////find a good location for scores
    //player 1
    ////2d location
    //glRasterPos2i(154, 20);
    ////3dlocation
    glRasterPos3i(154, 20,0);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, p1);

    //player 2
    ////2d location
    //glRasterPos2i(514, 20);
    ////3dlocation
    glRasterPos3i(514, 20,0);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, p2);
}

#endif // SCOREDISPLAY_H_INCLUDED
