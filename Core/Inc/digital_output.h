/*
 * digital_output.h
 *
 *  Created on: Mar 14, 2022
 *      Author: abaranska
 */

#ifndef INC_DIGITAL_OUTPUT_H_
#define INC_DIGITAL_OUTPUT_H_

#include "main.h"
#include "gpio.h"

class digital_output{
private:
	GPIO_TypeDef* _gpio_port;
	uint16_t _gpio_pin;

public:
	digital_output(GPIO_TypeDef* port, uint16_t pin)
		: _gpio_port{ port }, _gpio_pin{ pin } {}

	void set();
	void clr();
};

#endif /* INC_DIGITAL_OUTPUT_H_ */
