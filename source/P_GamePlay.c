/*
 * P_GamePlay.c
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#include "P_GamePlay.h"


int speed = 0, x_car = 128, game_state = 0;
int x_pink = 128, y_pink = SCREEN_HEIGHT-SPRITE_HEIGHT;
int touch = 0, enemy = 0;


void Gameplay_handleInput(enum ACTION a){
	if (game_state == 0 && a !=START) a = -1;
	switch(a){
	case JUMP :
		irqEnable(IRQ_TIMER1);
		Audio_PlaySoundEX(SFX_JUMP);
		break;
	case DOWN:
		if (speed > 0)speed--; break;
	case UP:
		if (speed < 5)speed++; break;
	case LEFT:
		if (x_car >= 70) x_car-=1; break;
	case RIGHT:
		if (x_car < 180) x_car++; break;
	case START:
		if (game_state == 0) game_state = 1;
		else game_state = 0;
		 Gameplay_GraphicsToggle();
	default:
		break;
	}
}

void Gameplay_Update(){
	P_Map16x16_scrolling_BG3(speed);
	P_Map16x16_scrolling_BG2_Sub(speed);

	Gameplay_Enemies();
	P_GraphicsMain_setCarPink(100, 100, false);
	if ( Get_TimerTicks1() == 0) {
		EraseJump(x_car);
		carTouched(x_pink, y_pink);
	} else {
		carJump(x_pink, y_pink);
	}
	updateScore(speed, touch, enemy);
	enemy = 0; touch = 0;
}


void P_Game(){
	if (game_state)
		Gameplay_Update();
	handleKeys();
	handleTouch();
}

void Gameplay_GraphicsToggle(){
	int i;
	for (i = 0; i<32*32; i++){
		BG_MAP_RAM(10)[i] = 0;
	}
	if (game_state == 0){
		writeMaxScore();
		speed = 0;
		P_Map16x16_scrolling_Init();
		REG_DISPCNT = ~(DISPLAY_BG1_ACTIVE) & ~(DISPLAY_BG3_ACTIVE) & ~(DISPLAY_BG0_ACTIVE) & ~(MODE_0_2D);
		REG_DISPCNT = MODE_0_2D | DISPLAY_BG1_ACTIVE |DISPLAY_BG2_ACTIVE;

		displayMaxScore_Start(game_state);
	}else {
		readMaxScore();
		REG_DISPCNT = ~(DISPLAY_BG1_ACTIVE) & ~(MODE_0_2D) & ~(DISPLAY_BG2_ACTIVE);
		REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG3_ACTIVE;
		displayMaxScore();
	}

}

void carTouched(int x_enemy, int y_enemy){
	if (abs(y_pink-POS_REDCAR) < SPRITE_HEIGHT/2){
		if (abs (x_car- x_enemy)< SPRITE_WIDTH/2){
			enemy = 50;
			Audio_PlaySoundEX(SFX_ENEMY);
		}
	}
}

void carJump(int x_enemy, int y_enemy){
	if (abs(y_pink-POS_REDCAR) < SPRITE_HEIGHT){
		if (abs (x_car- x_enemy)< SPRITE_WIDTH){
			y_pink = SCREEN_HEIGHT-SPRITE_HEIGHT;
			x_pink = rand()%111 + 70;
			P_GraphicsSub_setCarPink(x_pink, y_pink, true, 2);
			touch = 100;
		}
	}
}

void Gameplay_Enemies(){
	int sgn_x= rand()%3 -1;
	if (x_pink+sgn_x < 70 )
		x_pink =70;
	else if (x_pink+sgn_x > 180 )
		x_pink =180;
	else x_pink= x_pink+sgn_x;

	y_pink = (y_pink - 1)%192;

	if ((y_pink <0 && y_pink > SCREEN_HEIGHT-SPRITE_HEIGHT )||( game_state ==0)){
		y_pink =SCREEN_HEIGHT-SPRITE_HEIGHT;
		P_GraphicsSub_setCarPink(x_pink, y_pink, true, 2);
	}else{
		P_GraphicsSub_setCarPink(x_pink, y_pink, false, 2);
	}


}

int Get_Car_Pos(){return x_car;}
