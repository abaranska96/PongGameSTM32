/*
 * pong.h
 *
 *  Created on: Apr 6, 2022
 *      Author: abaranska
 */

#ifndef INC_PONG_H_
#define INC_PONG_H_

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

#include "joystick.h"
#include "display.h"

#include <array>

constexpr uint16_t max_paddle_y = 200;
constexpr uint16_t disp_height = 240;
constexpr uint8_t paddle_len = 40;

class pong{
private:
	enum{
		left_paddle = 16,
		left_bottom = 128,
		right_paddle = 4096
	};

	struct paddle_coords{
		uint16_t x, y;

		paddle_coords(): x{0}, y{ disp_height / 2 - paddle_len / 2 }{} //po utworzeniu instancji obiektu paddle coords otrzymujemy strukturę z x = 0 i y = 0 (konstruktor)

		paddle_coords& operator++(int);
		paddle_coords& operator--(int);
	};

	class game{
	private:
		paddle_coords left_paddle, right_paddle;
		const uint16_t width, height;

	public:
		game(uint16_t w, uint16_t h):
			left_paddle{}, right_paddle{}, width{ w }, height{ h }  {}

		const paddle_coords& get_left_paddle()const { return left_paddle; }
		const paddle_coords& get_right_paddle()const { return right_paddle; }

		paddle_coords& get_left_paddle() { return left_paddle; }
		paddle_coords& get_right_paddle() { return right_paddle; }
	};

	static bool user_paddle; //false -> left paddle, true -> right paddle is controlled by the user

public:
	static game game_board;
	static volatile bool display_game;
	static char logs[45];
	static void pongGame(void* params);
};


#endif /* INC_PONG_H_ */
