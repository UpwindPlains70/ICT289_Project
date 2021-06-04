#ifndef GLOBALTIMER_H
#define GLOBALTIMER_H

#define TIMER 5 //Physics call speed
#define TIMERMSECSA 50 //swing anim call speed
#define TIMERMSECSB 55 //swing anim call speed
#define TIMERMSECSPA 40 //power anim call speed
#define TIMERMSECSPB 45 //power anim call speed
//animation timers
float startTime, prevTime;
float currTime;
float timeSincePrevFrame;

static char label[100];
typedef enum {false, true} bool;

const float textColor[] = {0.0, 0.0, 0.0};
bool optionsMenuActive = false;
bool helpMenuActive = false;
bool gameStarted = false;
bool gameEnding = false;
bool gamePaused = false;

void drawString (char *s)
{
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

void startTimer()
{
    startTime = glutGet(GLUT_ELAPSED_TIME) / 1000.f;
    setPrevTime();
}


#endif // GLOBALTIMER_H
