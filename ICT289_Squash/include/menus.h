#ifndef MENUS_H
#define MENUS_H

#ifdef _WIN32
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif

    ///Include for customizization
#include "scoreDisplay.h"
#include "player.h"
#include "ball.h"
#include "physics.h"

#include "menusDisplay.h"
#include "QuitHandler.h"
#include "globals.h"

    //Light
const GLfloat light_position[] = {-28.0, -14.0, -92.0,1};

void processMainMenuEvents(int option);

void createMainMenu();


void startGame(){

    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    resetPlayerPos();
    resetBall(&ballArray[0]); ///Reset ball positio
    resetBallColor(&ballArray[0]); ///Reset ball color
    initPhysics(); ///Reset physics
    gameStarted = true; ///Allows ball to spawn
    glutTimerFunc(TIMER, physics, 0); ///Ball physics
    newGame(); ///Reset scoreboard
}

void resetGameSettings(){

    speedMod = defaultSpeedMod; ///Reset player speed
    swingSpeed = defaultSwingSpeed; ///Reset swing speed
    dropOff = defaultDropOff;  ///Reset ball start bounciness
    winScore = defaultWinScore;///reset points to win
}

void processOptionsEvents(int option){

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
        increaseBounciness();
        break;
    case 6: ///Decrease Ball Bounce on start
        decreaseBounciness();
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

void optionsMenu(){

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

void processHelpEvents(int option){

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

void helpMenu(){

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

void createQuitMenu(){

	// create the menu and
	// tell glut that "processMenuEvents" will
	// handle the events
	menu = glutCreateMenu(processMainMenuEvents);

	//add entries to our menu
	glutAddMenuEntry("Quit",6);

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processMainMenuEvents(int option){

	switch (option) {
		case 1 : ///Start Round (spawn ball & set pos)
             startGame();
             createMainMenu();
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
        case 5:  ///Display group pic
            gameEnding = true;
            createQuitMenu();
            break;
        case 6: ///Quit program
            exit(0);
            break;
	}
}

void createMainMenu(){

	// create the menu and
	// tell glut that "processMenuEvents" will
	// handle the events
	menu = glutCreateMenu(processMainMenuEvents);

	//add entries to our menu

	if(gameStarted == false){
        glutAddMenuEntry("Start Game",1);
        glutAddMenuEntry("Options",2);
        glutAddMenuEntry("Reset Game Setting",3);
	}
	glutAddMenuEntry("Help",4);
	glutAddMenuEntry("Quit",5);

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

#endif // MENUS_H
