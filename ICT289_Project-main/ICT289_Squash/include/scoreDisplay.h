#ifndef SCOREDISPLAY_H_INCLUDED
#define SCOREDISPLAY_H_INCLUDED

///Due to the nature of this code, scores are of a maximum of 9 as any further will lead to ascill code beyond 9;

//change values on top to alter score;
int plyr1Score = 0;
int plyr2Score = 0;

typedef enum {p1, p2, none} winnerStates;

int maxScore = 10;
int minScore = 1;
int defaultWinScore = 5;

int winScore = 5;

winnerStates gameWinner = none;

void WriteCaptions(void)
{
    //int to character
    char p1 = plyr1Score +'0';
    char p2 = plyr2Score +'0';

    //colour
    glColor3f(0.0, 0.0, 0.0);

    //////find a good location for scores
    //player 1
    ////3dlocation
    glRasterPos3i(0, 40,-26);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, p1);

    //player 2
    ////3dlocation
    glRasterPos3i(0, 40,-38);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, p2);
}

void increaseP1Score()
{
    if(plyr1Score+1 < winScore)
        plyr1Score++;
    else
    {   ///Game over P1 wins
        plyr1Score++;
        gameWinner = p1;
        ///Back to main menu
    }
}

void increaseP2Score()
{
    if(plyr1Score+1 < winScore)
        plyr2Score++;
    else
    {   ///Game over P2 wins
        plyr1Score++;
        gameWinner = p2;
        ///Back to main menu
    }
}

void newGame()
{
    plyr1Score = 0;
    plyr2Score = 0;
    gameWinner = none;
}

void increaseWinScore()
{
    if(winScore < maxScore)
        winScore++;
    else
        printf("Score is at maximim: %d\n", maxScore);
}

void decreaseWinScore()
{
    if(winScore > minScore)
        winScore--;
    else
        printf("Score is at minimum: %d\n", minScore);
}
#endif // SCOREDISPLAY_H_INCLUDED
