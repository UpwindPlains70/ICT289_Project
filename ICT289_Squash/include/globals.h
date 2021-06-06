#ifndef GLOBALS_H
#define GLOBALS_H

#ifdef _WIN32
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif

#define TIMER 4 //Physics call frequency
#define TIMERMSECSA 50 //swing anim call frequency P1
#define TIMERMSECSB 55 //swing anim call frequency P2

    ///Global animation timers
float startTime, prevTime;
float currTime;
float timeSincePrevFrame;

int menu;

    ///Used by menuDisplay
static char label[100];

typedef enum {false, true} bool;

const float textColor[] = {0.0, 0.0, 0.0};
bool optionsMenuActive = false;
bool helpMenuActive = false;
bool gameStarted = false;
bool gameEnding = false;

    ///Prints contents of 'label' typically
void drawString (char *s){

  unsigned int i;
  for (i = 0; i < strlen (s); i++)
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_10, s[i]);
}

void calcTimeSinceLastFrame(){

    currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    timeSincePrevFrame = currTime - prevTime;
}

void setPrevTime(){

    prevTime = currTime;
}

void startTimer(){

    startTime = glutGet(GLUT_ELAPSED_TIME) / 1000.f;
    setPrevTime();
}


#endif // GLOBALS_H
