#include "objectdisplay.h"

#include "player.h"
#include "menus.h"

void positionPlayer(){
    ///----------------------( drawing first character ) ------------------
    glPushMatrix();
    /// height and adding it to the Y as otherwise character is halfway into the ground
        glTranslatef(startingPos[0][0], startingPos[0][1], startingPos[0][2]); /// starting location of player1
        glTranslatef(playerArray[0].CoM[0], playerArray[0].CoM[1], playerArray[0].CoM[2]); /// move player1 based on CoM
        glRotatef(playerArray[0].currSwingAngle, 0, 1, 0);
        drawPlayer(0, playerColours[0]);          // passing index for player1, first element of player array and Array of a 3 element RGB array
        drawRacket(0);
        collisionPlayer(0, &ballArray[0]);

    glPopMatrix();
///----------------------( drawing second character ) ----------
    glPushMatrix();

            //NEED TO COMPENSATE FOR CoM TRANSLATE
        glTranslatef(startingPos[1][0], startingPos[1][1], startingPos[1][2]); /// starting location of player2
        glTranslatef(playerArray[1].CoM[0], playerArray[1].CoM[1], playerArray[1].CoM[2]); /// move player2 based on CoM
        glRotatef(playerArray[1].currSwingAngle, 0, 1, 0);
        drawPlayer(1, playerColours[1]); // passing index for player1, second element of player array
        drawRacket(1);
        collisionPlayer(1, &ballArray[0]);

    glPopMatrix();

}

void menuHandler(){
    if(optionsMenuActive == true)
        writeOptionsMenuDisplay();

    if(helpMenuActive == true)
        writeHelpDisplay();

    if(gameWinner == p1)
        playerOneWinsDisplay();
    else if(gameWinner == p2)
        playerTwoWinsDisplay();

        ///Add game ball to the world
    if(gameStarted == true){
        glPushMatrix();
            drawGameBall(&ballArray[0]);
        glPopMatrix();
    }
}

void drawPowerBox(){
    if(playerArray[1].swingMode == powering || playerArray[1].swingMode == cooling)
    {
        glPushMatrix();
            drawPlayerTwoPower();
        glPopMatrix();
    }

    if(playerArray[0].swingMode == powering || playerArray[0].swingMode == cooling)
    {
        glPushMatrix();
            drawPlayerOnePower();
        glPopMatrix();
    }
}
