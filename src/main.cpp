#include <cstdlib>   // Generate random numbers
#include <ctime>     // Get time as seed
#include <ncurses.h> // Get Keyboard input and provide console io

#include "../include/config.hpp"
#include "../include/snake.hpp"
#include "../include/terminal.hpp"
#include "../include/keyboard.hpp"

int main(void) {
	srand(static_cast<unsigned int>(time(nullptr)));

	int sizeX, sizeY;
	Terminal terminal;
	terminal.getTerminalSize(&sizeX, &sizeY);
	Snake snake(sizeX, sizeY);
	Keyboard keyboard;
	snake.initMatrix();
	while (1) {
		int actualMovedDirection = snake.getDirection();
		int inputDirection = keyboard.getKey(actualMovedDirection);
		snake.setDirection(inputDirection);
		snake.move();
		snake.shift();
		snake.show();
		napms(400 - SPEED*70); // 500 to 100 ms
	}
	return 0;
}
