#ifndef SCOREDISPLAY_H_INCLUDED
#define SCOREDISPLAY_H_INCLUDED

////Due to the nature of this code, scores are of a maximum of 9 as any further will lead to ascill code beyond 9;

#include "Geometry.h"

//change values on top to alter score;
int plyr1Score = 0;
int plyr2Score = 0;

typedef enum {p1, p2, none} winnerStates;

const int maxScore = 9;
const int minScore = 1;
const int defaultWinScore = 5;

int winScore = 5;

winnerStates gameWinner = none;

const Face3D p1ScorePos = {5, 40,-26};
const Face3D p2ScorePos = {5, 40,-38};


void WriteScores(void)
{
    //int to character
    char p1 = plyr1Score +'0';
    char p2 = plyr2Score +'0';

    //colour
    glColor3f(0.0, 0.0, 0.0);

    //////find a good location for scores
    //player 1
    ////3dlocation
    glRasterPos3i(p1ScorePos.x, p1ScorePos.y, p1ScorePos.z);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, p1);

    //player 2
    ////3dlocation
    glRasterPos3i(p2ScorePos.x, p2ScorePos.y, p2ScorePos.z);
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
    if(plyr2Score+1 < winScore)
        plyr2Score++;
    else
    {   ///Game over P2 wins
        plyr2Score++;
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
