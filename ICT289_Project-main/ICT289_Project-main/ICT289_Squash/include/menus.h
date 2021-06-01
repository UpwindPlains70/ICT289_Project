#ifndef MENUS_H
#define MENUS_H

#include <GL/freeglut.h>
#include <GL/glut.h>

#include "scoreDisplay.h"
#include "player.h"
#include "menusDisplay.h"
#include "ball.h"

typedef enum {false, true} bool;

bool optionsMenuActive = false;
bool helpMenuActive = false;
bool gameStarted = false;



void startGame()
{
    resetPlayerPos();
    resetBall(); ///Reset ball color & position
    initPositions(); ///Reset physics
    gameStarted = true; ///Allows ball to spawn
    hasHitBall[0] = FALSE;
    hasHitBall[1] = FALSE;
    newGame(); ///Reset scoreboard
}

void resetGameSettings()
{
    speedMod = defaultSpeedMod; ///Reset player speed
    swingSpeed = defaultSwingSpeed; ///Reset swing speed
    ///Reset ball start bounciness
    winScore = defaultWinScore;///reset points to win
}

void processOptionsEvents(int option)
{
    switch(option)
    {
    case 1: ///Increase player speed
        increasePlayerSpeed();
        break;
    case 2: ///Decrease player speed
        decreasePlayerSpeed();
        break;
    case 3: ///Increase Swing speed
        increaseSwingSpeed();
        break;
    case 4: ///Decrease Swing speed
        decreaseSwingSpeed();
        break;
    case 5: ///Increase Ball Bounce on start
        break;
    case 6: ///Decrease Ball Bounce on start
        break;
    case 7: ///Increase Points to win
        increaseWinScore();
        break;
    case 8: ///Decrease Points to win
        decreaseWinScore();
        break;
    case 9: ///Return to main menu
        optionsMenuActive = false;
        createMainMenu();
        break;
    }
}

void optionsMenu()
{
    int menu;

	// create the menu and
	// tell glut that "processMenuEvents" will
	// handle the events
	menu = glutCreateMenu(processOptionsEvents);

	//add entries to our menu
	glutAddMenuEntry("Increase Player Speed",1);
	glutAddMenuEntry("Decrease Player Speed",2);

	glutAddMenuEntry("Increase Swing Speed",3);
	glutAddMenuEntry("Decrease Swing Speed",4);

	glutAddMenuEntry("Increase Ball Bounce",5);
	glutAddMenuEntry("Decrease Ball Bounce",6);


	glutAddMenuEntry("Increase Points to Win",7);
	glutAddMenuEntry("Decrease Points to Win",8);
	glutAddMenuEntry("Main Menu",9);

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/*
void optionsMenu()
{
    printf("------ Options -------\n");
    printf("Adjust game parameters");

    printf("Player Speed");
    printf("Swing Speed");
    printf("Ball hardness/softness on start");
    printf("Points to Win");
}*/

void processHelpEvents(int option)
{
    switch(option)
    {
    case 1:
        helpMenuActive = false;
        startGame();
        break;
    case 2:
        helpMenuActive = false;
        createMainMenu();
        break;
    }
}

void helpMenu()
{
    int menu;

	// create the menu and
	// tell glut that "processMenuEvents" will
	// handle the events
	menu = glutCreateMenu(processHelpEvents); ///Only uses the main menu option

	glutAddMenuEntry("Start Game",2);
	glutAddMenuEntry("Main Menu",2);

	//writeOptionsMenuDisplay();
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processMainMenuEvents(int option) {

	switch (option) {
		case 1 : ///Start Round (spawn ball & set pos)
             startGame();
			 break;
		case 2 : ///Options
		     optionsMenuActive = true;
		     optionsMenu();
			 break;
		case 3 : ///Reset settings
			 resetGameSettings();
			 break;
		case 4 : ///Help
		     helpMenuActive = true;
			 helpMenu();
			 break;
        case 5:  ///Quit program
            exit(0);
            break;
	}
}

void createMainMenu() {

	int menu;

	// create the menu and
	// tell glut that "processMenuEvents" will
	// handle the events
	menu = glutCreateMenu(processMainMenuEvents);

	//add entries to our menu
	glutAddMenuEntry("Start Game",1);
	glutAddMenuEntry("Options",2);
	glutAddMenuEntry("Reset Game Setting",3);
	glutAddMenuEntry("Help",4);
	glutAddMenuEntry("Quit",5);

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

#endif // MENUS_H
