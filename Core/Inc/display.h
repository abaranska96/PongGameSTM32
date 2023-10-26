/*
 * display.h
 *
 *  Created on: Mar 22, 2022
 *      Author: abaranska
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "cmsis_os.h"
#include "pong.h"

class display{
public:
	static bool clear_display;
	static osSemaphoreId_t refresh_display;
    static void SPIsimpleText(void* params);
};


#endif /* INC_DISPLAY_H_ */
