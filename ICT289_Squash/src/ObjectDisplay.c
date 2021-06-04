#include "objectdisplay.h"
#include "../include/player.h"

void positionPlayer(){

}

void menuHandler(){

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
