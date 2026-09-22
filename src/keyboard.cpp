#include <curses.h>

#include "../include/config.hpp"
#include "../include/keyboard.hpp"

Keyboard::Keyboard(void) {
	direction = RIGHT;
}

int Keyboard::getKey(int lastDirection) {
	int key;
	while ((key = getch()) != ERR) {
		switch(key) {
			case KEY_UP:    if ( lastDirection != DOWN ) direction = UP;    break;
			case KEY_DOWN:  if ( lastDirection != UP   ) direction = DOWN;  break;
			case KEY_LEFT:  if ( lastDirection != RIGHT) direction = LEFT;  break;
			case KEY_RIGHT: if ( lastDirection != LEFT ) direction = RIGHT; break;
			default: break;
		}
	}
	return direction;
}
