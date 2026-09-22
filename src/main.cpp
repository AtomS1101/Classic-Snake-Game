#include <stdio.h>
#include <string>
#include <cstdlib>   // Generate random numbers
#include <ctime>     // Get time as seed
#include <ncurses.h> // Get Keyboard input and provide console io

#include "../include/config.hpp"
#include "../include/snake.hpp"
#include "../include/terminal.hpp"
#include "../include/keyboard.hpp"

int main(int argc, char *argv[]) {
	int speed = SPEED;
	int food  = FOOD;

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg == "-h") {
			printf(" Usage: %s [-s speed] [-f food]\n", argv[0]);
			return 0;
		}
		if (arg == "-s" && i + 1 < argc) {
			speed = atoi(argv[++i]);
		} else if (arg == "-f" && i + 1 < argc) {
			food = atoi(argv[++i]);
		}
	}

	int sizeX, sizeY;
	Terminal terminal;
	terminal.getTerminalSize(&sizeX, &sizeY);
	Snake snake(sizeX, sizeY, speed, food);
	Keyboard keyboard;
	snake.initMatrix();
	while (1) {
		int actualMovedDirection = snake.getDirection();
		int inputDirection = keyboard.getKey(actualMovedDirection);
		snake.setDirection(inputDirection);
		snake.move();
		snake.shift();
		snake.show();
		napms(400 - speed * 70); // 50 ~ 370 ms
	}
	return 0;
}
