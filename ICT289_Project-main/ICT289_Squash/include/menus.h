#ifndef MENUS_H
#define MENUS_H

#include <GL/freeglut.h>
#include <GL/glut.h>

void startGame()
{

}

void resetGameSettings()
{

}

void processOptionsEvents(int option)
{
    switch(option)
    {
    case 1: ///Increase player speed
        break;
    case 2: ///Decrease player speed
        break;
    case 3: ///Increase Swing speed
        break;
    case 4: ///Decrease Swing speed
        break;
    case 5: ///Increase Ball Bounce on start
        break;
    case 6: ///Decrease Ball Bounce on start
        break;
    case 7: ///Increase Points to win
        break;
    case 8: ///Decrease Points to win
        break;
    case 9: ///Return to main menu
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

	glutAddMenuEntry("Increase Ball Bounce",3);
	glutAddMenuEntry("Decrease Ball Bounce",4);

	glutAddMenuEntry("Increase Swing Speed",5);
	glutAddMenuEntry("Decrease Swing Speed",6);

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

void helpMenu()
{
    printf("------ Help ------\n");
    printf("Player One controls -------\n");
    printf("Arrow keys = movement\n");
    printf("space bar = hit/swing\n\n");

    printf("Player Tow controls -------\n");
    printf("WASD = movement (Forward, Left, Back, Right)\n");
    printf("F = hit/swing\n\n");
}

void processMainMenuEvents(int option) {

	switch (option) {
		case 1 : ///Start Round (spawn ball & set pos)
             startGame();
			 break;
		case 2 : ///Options
		     optionsMenu();
			 break;
		case 3 : ///Reset settings
			 resetGameSettings();
			 break;
		case 4 : ///Help
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
	glutAddMenuEntry("Start",1);
	glutAddMenuEntry("Options",2);
	glutAddMenuEntry("Reset Game Setting",3);
	glutAddMenuEntry("Help",4);
	glutAddMenuEntry("Quit",5);

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

#endif // MENUS_H
