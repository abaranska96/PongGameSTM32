/*
 * digital_input.h
 *
 *  Created on: Mar 14, 2022
 *      Author: abaranska
 */

#ifndef INC_DIGITAL_INPUT_H_
#define INC_DIGITAL_INPUT_H_

#include "main.h"
#include "gpio.h"

class digital_input{
private:
	GPIO_TypeDef* _gpio_port;
	uint16_t _gpio_pin;

public:
	digital_input(GPIO_TypeDef* port, uint16_t pin)
		: _gpio_port(port), _gpio_pin(pin){ }
	bool read();
};

#endif /* INC_DIGITAL_INPUT_H_ */
