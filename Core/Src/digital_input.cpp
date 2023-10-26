/*
 * digital_input.cpp
 *
 *  Created on: Mar 14, 2022
 *      Author: abaranska
 */

#include "digital_input.h"

bool digital_input::read(){
	return HAL_GPIO_ReadPin(_gpio_port, _gpio_pin);
}
