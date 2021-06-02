#ifndef OPTIONSDISPLAY_H
#define OPTIONSDISPLAY_H

#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/glut.h>

#include "scoreDisplay.h"
#include "player.h"
#include "ball.h"

static char label[100];

void
drawString (char *s)
{
  unsigned int i;
  for (i = 0; i < strlen (s); i++)
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_10, s[i]);
};

void drawMenuBackground()
{
  glColor3f(0.8, 0.8, 0.8);
  glBegin(GL_POLYGON);
        glVertex3f(10,8, -10);
        glVertex3f(10,50, -10);
        glVertex3f(10,50, -55);
        glVertex3f(10,8, -55);
  glEnd();
}

void writeOptionsMenuDisplay(void)
{
    drawMenuBackground();
  glColor3f(0.0, 0.0, 0.0);
  sprintf (label, "Options Menu");
  glRasterPos3i (12, 45,-24);
  drawString (label);

        ///Display current player speed
  sprintf (label, "Player speed = %.1f ", speedMod);
  glRasterPos3i (12, 37,-20);
  drawString (label);

          ///Display current points to win
  sprintf (label, "Points to win = %d ", winScore);
  glRasterPos3i (12, 22,-20);
  drawString (label);

        ///Display current swing speed
  sprintf (label, "Player swing speed = %.1f ", swingSpeed);
  glRasterPos3i (12, 32,-15);
  drawString (label);

        ///Display ball bouncyness on start
  sprintf (label, "Ball Bounciness on start = %.1f ", speedMod);
  glRasterPos3i (12, 27,-13);
  drawString (label);

}

void writeHelpDisplay()
{
  drawMenuBackground();

  glColor3f(0.0, 0.0, 0.0);
  sprintf (label, "Help Menu");
  glRasterPos3i (12, 45,-26);
  drawString (label);

  sprintf (label, "--- Player One controls ---");
  glRasterPos3i (12, 39,-14);
  drawString (label);
  sprintf (label, "Arrow keys = movement");
  glRasterPos3i (12, 35,-16);
  drawString (label);
  sprintf (label, "space bar = hit/swing");
  glRasterPos3i (12, 31,-16);
  drawString (label);

  sprintf (label, "--- Player Two controls ---");
  glRasterPos3i (12, 25,-14);
  drawString (label);
  sprintf (label, "WASD keys = movement");
  glRasterPos3i (12, 21,-16);
  drawString (label);
  sprintf (label, "(Forward, Left, Back, Right)");
  glRasterPos3i (12, 17,-16);
  drawString (label);
  sprintf (label, "F = hit/swing");
  glRasterPos3i (12, 13,-16);
  drawString (label);
}

void playerOneWinsDisplay()
{
  glColor3f(0.0, 0.0, 0.0);
  sprintf (label, "Player One Wins!!");
  glRasterPos3i (5, 36,-22);
  drawString (label);
}

void playerTwoWinsDisplay()
{
  glColor3f(0.0, 0.0, 0.0);
  sprintf (label, "Player Two Wins!!");
  glRasterPos3i (5, 36,-22);
  drawString (label);
}

#endif //OPTIONSDISPLAY_H
