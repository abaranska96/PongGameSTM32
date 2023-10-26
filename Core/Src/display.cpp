/*
 * display.cpp
 *
 *  Created on: Mar 22, 2022
 *      Author: abaranska
 */

#include "stm32f4xx.h"

#include <stdio.h>
#include <string.h>

#include "display.h"
#include "ili9341.h"
#include "ili9341_touch.h"
#include "fonts.h"
#include "testimg.h"
#include "keyboard.h"
#include "joystick.h"

static char buttons_bin[20] = {0};
osSemaphoreId_t display::refresh_display{ osSemaphoreNew(1, 0, NULL) };
bool display::clear_display{ false };

void binary_to_string(uint16_t bin_value){
	memset(buttons_bin, '0', 16);

	for(uint8_t i = 0; i < 16; ++i){
		if(bin_value & (1 << i)){
			buttons_bin[15 - i] = '1';
		}
	}
}

void display::SPIsimpleText(void* params){
	static uint8_t i = 0;

	ILI9341_Unselect();
	ILI9341_Init();
	osDelay(3000);

	ILI9341_FillScreen(ILI9341_BLUE);

	while(1){
		osSemaphoreAcquire(refresh_display, osWaitForever); //wait for semaphore

		if(pong::display_game){ //display game
			auto left_paddle = pong::game_board.get_left_paddle();
			auto right_paddle = pong::game_board.get_right_paddle();

			for(uint16_t h = 0; h < ILI9341_HEIGHT; ++h){
				for(uint16_t w = 0; w < ILI9341_WIDTH; ++w){
					uint16_t color = ILI9341_BLACK;

					if(w < 4){
						if(h >= left_paddle.y && h - left_paddle.y < 40){
							color = ILI9341_WHITE;
						}
					}
					else if(w >= 316){
						if(h >= right_paddle.y && h - right_paddle.y < 40){
							color = ILI9341_WHITE;
						}
					}
					ILI9341_DrawPixel(w, h, color);
				}
			}

			osDelay(5);
		}
		else{				    //display logs
			if(i == 24 || clear_display){
				i = 0;
				clear_display = false;
				ILI9341_FillScreen(ILI9341_BLACK);
			}

			ILI9341_WriteString(0, 10*i++, pong::logs, Font_7x10, ILI9341_WHITE, ILI9341_BLACK);
			osDelay(500);
		}
	}

	osThreadTerminate(NULL);
}
