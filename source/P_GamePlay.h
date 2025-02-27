/*
 * P_GamePlay.h
 *
 * Created on: 		December 18, 2020
 * Authors :	 	Durand Mathilde <mathilde.durand@epfl.ch> &
 * 					Emma Hoggett <emma.hoggett@epfl.ch>
 */

#pragma once

#include <nds.h>
#include "BumpNJumpDefines.h"
#include "P_Audio.h"
#include "P_Map16x16.h"
#include <nds/arm9/sound.h>		// sound functions
#include "soundbank.h"
#include "P_Score.h"
#include "P_Timer.h"
#include "P_Controls.h"


void Gameplay_Init();
void Gameplay_handleInput(enum ACTION a);

void Gameplay_Update();
void Gameplay_GraphicsToggle();
void P_Game();
void Gameplay_Enemies();
void Gameplay_RoadBoundaries(int pos, int* left, int* right);
void carTouched(int x_enemy, int y_enemy);
void carJump();
int Get_Car_Pos();
