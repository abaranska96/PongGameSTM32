/*
 * joystick.h
 *
 *  Created on: Mar 15, 2022
 *      Author: abaranska
 */

#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

#include "main.h"
#include "cmsis_os.h"

class joystick{
private:
	struct coords{
		int x;
		int y;
	};

	static ADC_HandleTypeDef& adc_handle;
	static void update_position();
	static uint16_t adc_values[2];
	static osSemaphoreId_t adc_sem;

public:
	static volatile coords position;
	static void inputControl(void* params);
	static void adc_callback();
};


#endif /* INC_JOYSTICK_H_ */
