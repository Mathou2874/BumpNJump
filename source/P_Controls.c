/*
 * P_Controls.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_Controls.h"
#include "P_GamePlay.h"


int  comptBg=192, jump = 0, iter = 50;


void handleKeys(){
		scanKeys();
		unsigned keys = keysHeld();
    	//Modify position of the sprite accordingly
    	if((keys & KEY_RIGHT)) Gameplay_handleInput(RIGHT);
    	if((keys & KEY_DOWN)) Gameplay_handleInput(DOWN);
    	if((keys & KEY_UP)) Gameplay_handleInput(UP);
    	if((keys & KEY_LEFT)) Gameplay_handleInput(LEFT);
    	if ((keys & KEY_A)) Gameplay_handleInput(JUMP);
    	if ((keysDown() & KEY_START))Gameplay_handleInput(START);
}

void handleTouch(){
	scanKeys();
	touchPosition touch;
	int x, y;
	if ((keysDown() & KEY_TOUCH) && jump == 0){
		touchRead(&touch);
		x = touch.px; y = touch.py;
		if (x < 128)  Gameplay_handleInput(RIGHT);
		else if (x >= 128) Gameplay_handleInput(LEFT);
		if (y < 96)  Gameplay_handleInput(UP);
		else if (y >= 96) Gameplay_handleInput(DOWN);
		iter--;
		if (iter != 0)jump = 1;
		else jump = 0;

	} else if ((keysDown() & KEY_TOUCH) && jump == 1){
		 Gameplay_handleInput(JUMP);
		 jump = 0;
	}
}



