#ifndef SCOREDISPLAY_H_INCLUDED
#define SCOREDISPLAY_H_INCLUDED

///Due to the nature of this code, scores are of a maximum of 9 as any further will lead to ascill code beyond 9;

//change values on top to alter score;
int plyr1Score = 0;
int plyr2Score = 0;

int maxScore = 5;

void WriteCaptions(void)
{
    //int to character
    char p1 = plyr1Score +'0';
    char p2 = plyr2Score +'0';

    //colour
    glColor3f(0.0, 0.0, 0.0);

    //////find a good location for scores
    //player 1
    ////2d location
    //glRasterPos2i(80, 20);
    ////3dlocation
    glRasterPos3i(0, 40,-26);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, p1);

    //player 2
    ////2d location
    //glRasterPos2i(514, 20);
    ////3dlocation
    glRasterPos3i(0, 40,-38);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, p2);
}

void increaseP1Score()
{
    if(plyr1Score+1 < maxScore)
        plyr1Score++;
    else
    {   ///Game over P1 wins
        plyr1Score++;
        printf("Player One Wins!!!\n");
        printf("%d  to %d", plyr1Score, plyr2Score);
newGame();
        ///Back to main menu
    }
}

void increaseP2Score()
{
    if(plyr1Score+1 < maxScore)
        plyr2Score++;
    else
    {   ///Game over P2 wins
        plyr1Score++;
        printf("Player One Wins!!!\n");
        printf("%d  to %d", plyr1Score, plyr2Score);
    newGame();
        ///Back to main menu
    }
}

void newGame()
{
    plyr1Score = 0;
    plyr2Score = 0;
}
#endif // SCOREDISPLAY_H_INCLUDED
