/*
 * keyboard.h
 *
 *  Created on: Mar 14, 2022
 *      Author: abaranska
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include "digital_input.h"
#include "digital_output.h"

class keyboard{
private:
	static digital_input cols[4];
	static digital_output rows[4];

public:
	static volatile uint16_t keyboard_flags;
	static void inputProcess(void* params);
};


#endif /* INC_KEYBOARD_H_ */
