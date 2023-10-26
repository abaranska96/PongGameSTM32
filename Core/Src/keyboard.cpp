/*
 * keyboard.cpp
 *
 *  Created on: Mar 14, 2022
 *      Author: abaranska
 */

#include "keyboard.h"
#include "main.h"
#include "cmsis_os.h"
#include "dwt_stm32_delay.h"

constexpr uint8_t debouncing_period = 10;

volatile uint16_t keyboard::keyboard_flags{ 0 };

static const TickType_t xDelayMs = pdMS_TO_TICKS( 100 );

digital_input keyboard::cols[4]{ //inicjalizacja tablicy przechowującej
	{ COL1_GPIO_Port, COL1_Pin },//obiekty reprezentujące piny wejściowe
	{ COL2_GPIO_Port, COL2_Pin },//czyli kolumny klawiatury
	{ COL3_GPIO_Port, COL3_Pin },
	{ COL4_GPIO_Port, COL4_Pin }
};

digital_output keyboard::rows[4]{ //inicjalizacja tablicy przechowującej
	{ ROW1_GPIO_Port, ROW1_Pin }, //obiekty reprezentujące piny wyjściowe
	{ ROW2_GPIO_Port, ROW2_Pin }, //czyli rzędy klawiatury
	{ ROW3_GPIO_Port, ROW3_Pin },
	{ ROW4_GPIO_Port, ROW4_Pin }
};

void keyboard::inputProcess(void* params){
	static uint16_t tmp_flags; //zmienna tymczasowa do przechowywania chwilowego stanu klawiatury
	static uint8_t shift_cnt = 0; //licznik do przesunięc bitowych

	while(1){
		shift_cnt = 0;
		tmp_flags = 0;

		for(uint8_t i = 0; i < 4; ++i){
			rows[i].clr(); //multipleksowanie klawiatury

			DWT_Delay_us(250);

			for(uint8_t j = 0; j < 4; ++j){
				if(cols[j].read() == false){ //jeśli przycisk jest wciśnięty
					tmp_flags |= (1 << shift_cnt); //to ustaw odpowiadający mu bit
				} else {
					tmp_flags &= ~(1 << shift_cnt); //wykasuj odpowiadający mu bit
				}
				shift_cnt++;
			}
			rows[i].set();
		}

		//Make sure that only one key is pressed in time: BECAUSE OF GHOSTING INSIDE BUTTON MATRIX WITHOUT DIODES
		uint8_t numPressed = 0;
		for(uint8_t i = 0; i < 4; ++i)
		{
			if(tmp_flags & (0x01 << i)) ++numPressed;
		}
		keyboard_flags = tmp_flags;
		//if(tmp_flags) keyboard_flags = tmp_flags;
		//else keyboard_flags = 0;

		vTaskDelay(xDelayMs);
	}

	osThreadTerminate(NULL);
}

