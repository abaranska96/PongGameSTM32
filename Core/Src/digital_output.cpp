/*
 * digital_output.cpp
 *
 *  Created on: Mar 14, 2022
 *      Author: abaranska
 */

#include "digital_output.h"


void digital_output::set(){
	HAL_GPIO_WritePin(_gpio_port, _gpio_pin, GPIO_PIN_SET);
}
void digital_output::clr(){
	HAL_GPIO_WritePin(_gpio_port, _gpio_pin, GPIO_PIN_RESET);
}
