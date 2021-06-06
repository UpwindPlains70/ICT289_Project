#ifndef MENUSDISPLAY_H
#define MENUSDISPLAY_H

#include <stdio.h>
#ifdef _WIN32
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif

#include "scoreDisplay.h"
#include "player.h"
#include "ball.h"
#include "physics.h"
#include "globals.h"

const float backgroundColor[] = {0.8, 0.8, 0.8};

    //menu Background coordinates
const float backgroundBL[] = {10, 8, -10};
const float backgroundTL[] = {10, 50, -10};
const float backgroundTR[] = {10, 50, -55};
const float backgroundBR[] = {10, 8, -55};

    //menu title coordinates
const int menuTitleDisp[] = {12, 45,-26};

    //Options menu coordinates
const int speedModDisp[] = {12, 37, -20};
const int winScoreDisp[] = {12, 22, -20};
const int swingSpeedDisp[] = {12, 32, -13};
const int dropOffDisp[] = {12, 27, -17};

    //Help player 1 coordinates
const int plyr1ControlsTitle[] = {12, 39,-14};
const int plyr1Movement[] = {12, 35,-16};
const int plyr1Swing[] = {12, 31,-16};

    //Help player 2 coordinates
const int plyr2ControlsTitle[] = {12, 25,-14};
const int plyr2Movement[] = {12, 21,-16};
const int plyr2MoveKeys[] = {12, 17,-16};
const int plyr2Swing[] = {12, 13,-16};

    //Position for win text
const int plyrWinDisp[] = {5, 36,-22};

    ///Define menu background
void drawMenuBackground(){

  glColor3fv(backgroundColor);
  glBegin(GL_POLYGON);
        glVertex3fv(backgroundBL); //Bottom left
        glVertex3fv(backgroundTL); //Top left
        glVertex3fv(backgroundTR); //Top right
        glVertex3fv(backgroundBR); //Bottom right
  glEnd();
}

    ///Create everything related to options
    /// + new menu options
void writeOptionsMenuDisplay(){

    drawMenuBackground();
  glColor3fv(textColor);
    sprintf (label, "Options Menu");
  glRasterPos3iv(menuTitleDisp);
  drawString (label);

        ///Display current player speed
    sprintf (label, "Player speed (M) = %.1f ", speedMod);
  glRasterPos3iv(speedModDisp);
  drawString (label);

          ///Display current points to win
    sprintf (label, "Points to win (V) = %d ", winScore);
  glRasterPos3iv(winScoreDisp);
  drawString (label);

        ///Display current swing speed
    sprintf (label, "Player swing speed (N) = %.1f ", swingSpeed);
  glRasterPos3iv(swingSpeedDisp);
  drawString (label);

        ///Display ball bouncyness on start
    sprintf (label, "Initial Bounciness (B) = %.1f ", dropOff);
  glRasterPos3iv(dropOffDisp);
  drawString (label);

}

    ///Create 3D text with relavent information
    ///Also change menu options
void writeHelpDisplay(){

  drawMenuBackground();

  glColor3fv(textColor);
    sprintf (label, "Help Menu");
  glRasterPos3iv(menuTitleDisp);
  drawString (label);

    sprintf (label, "--- Player One controls ---");
  glRasterPos3iv(plyr1ControlsTitle);
  drawString (label);
    sprintf (label, "Arrow keys = movement");
  glRasterPos3iv(plyr1Movement);
  drawString (label);
    sprintf (label, "space bar = hit/swing");
  glRasterPos3iv(plyr1Swing);
  drawString (label);

    sprintf (label, "--- Player Two controls ---");
  glRasterPos3iv(plyr2ControlsTitle);
  drawString (label);
    sprintf (label, "WASD keys = movement");
  glRasterPos3iv(plyr2Movement);
  drawString (label);
    sprintf (label, "(Forward, Left, Back, Right)");
  glRasterPos3iv(plyr2MoveKeys);
  drawString (label);
    sprintf (label, "F = hit/swing");
  glRasterPos3iv(plyr2Swing);
  drawString (label);
}

    ///Create 3D text displaying P1 as Winner
void playerOneWinsDisplay(){

  glColor3fv(textColor);
    sprintf (label, "Player One Wins!!");
  glRasterPos3iv(plyrWinDisp);
  drawString (label);
}

    ///Create 3D text displaying P2 as Winner
void playerTwoWinsDisplay(){

  glColor3fv(textColor);
    sprintf (label, "Player Two Wins!!");
  glRasterPos3iv(plyrWinDisp);
  drawString (label);
}

#endif //menusDISPLAY_H
