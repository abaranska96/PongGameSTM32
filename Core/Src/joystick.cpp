/*
 * joystick.cpp
 *
 *  Created on: Mar 15, 2022
 *      Author: abaranska
 */

#include <string.h>
#include <stdio.h>

#include "joystick.h"
#include "usart.h"

uint16_t joystick::adc_values[2]{ 0 }; //inicjalizacja zmiennych wartościami początkowymi
volatile joystick::coords joystick::position{ 0 };
osSemaphoreId_t joystick::adc_sem{ osSemaphoreNew(1, 1, NULL) }; //utworzenie semafora do kontroli adc

void joystick::inputControl(void* params){
	HAL_ADC_Start_DMA(&adc_handle, (uint32_t*)adc_values, 2); //rozpocznij konwersje
	osSemaphoreAcquire(adc_sem, osWaitForever); //pobierz semafor (jeśli nie jest dostępny to czekaj)
	static uint8_t buffer[50];

	while(1){
		update_position(); //zamień wartości otrzymane z adc na wyjście joysticka
		sprintf((char*)buffer, "x axis: %4d, y axis: %4d\r\n", position.x, position.y);
		HAL_UART_Transmit(&huart1, buffer, strlen((const char*)buffer), HAL_MAX_DELAY);
		HAL_ADC_Start_DMA(&adc_handle, (uint32_t*)adc_values, 2); //rozpocznij konwersje
		osSemaphoreAcquire(adc_sem, osWaitForever); //pobierz semafor (jeśli nie jest dostępny to czekaj)
	}

	osThreadTerminate(NULL);
}

void joystick::update_position(){
	auto x = position.x = position.x * 0.9 + 0.1 * adc_values[0];
	auto y = position.y = position.y * 0.9 + 0.1 * adc_values[1];
}

void joystick::adc_callback(){  //rutyna przerwania
	osSemaphoreRelease(adc_sem);//zwolnij semafor aby zezwolić na konwersje
}
