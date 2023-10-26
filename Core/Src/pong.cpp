/*
 * pong.cpp
 *
 *  Created on: Apr 6, 2022
 *      Author: abaranska
 */

#include <stdio.h>

#include "pong.h"
#include "ili9341.h"
#include "display.h"

#include "keyboard.h"

volatile bool pong::display_game{ false };
bool pong::user_paddle { false };
char pong::logs[45]{ 0 };
pong::game pong::game_board{ ILI9341_WIDTH, ILI9341_HEIGHT };

void pong::pongGame(void* params){
	while(1){
		sprintf(logs, "x axis: %4d, y axis: %4d", joystick::position.x, joystick::position.y);
		//sprintf(logs, "keyboard: %u", keyboard::keyboard_flags);

		//game ctrl
		if(keyboard::keyboard_flags & pong::left_bottom){
			display_game = !display_game;
			if(display_game){
				display::clear_display = true;
			}
			keyboard::keyboard_flags &= ~0x0080;
			osDelay(2000);
		}

		if(display_game){
			if(keyboard::keyboard_flags & pong::left_paddle){
				user_paddle = false;

				keyboard::keyboard_flags &= ~pong::left_paddle;
			}
			else if(keyboard::keyboard_flags & pong::right_paddle){
				user_paddle = true;

				keyboard::keyboard_flags &= ~pong::right_paddle;
			}

			auto& paddle = (user_paddle? game_board.get_right_paddle() : game_board.get_left_paddle());

			osSemaphoreRelease(display::refresh_display);
		}
		else{
			osDelay(1000);
			osSemaphoreRelease(display::refresh_display);
		}
		osDelay(5);
	}

	osThreadTerminate(NULL);
}

pong::paddle_coords& pong::paddle_coords::operator++(int){ //przeciążenie operatora inkrementacji ("zwiększanie" koordynatów paddle`a po y)
	if(y < max_paddle_y){
		y++;
	}

	return *this;
}

pong::paddle_coords& pong::paddle_coords::operator--(int){ //przeciążenie operatora dekrementacji ("zmniejszanie" koordynatów paddle`a po y)
	if(y > 0){
		y--;
	}

	return *this;
}
