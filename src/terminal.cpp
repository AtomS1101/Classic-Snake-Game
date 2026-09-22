#include <cstdlib>   // Provides exit()
#include <ncurses.h> // Get Keyboard input and provide console io

#include "../include/config.hpp"
#include "../include/terminal.hpp"

Terminal::Terminal(void) {
	initscr();             // Start ncurses
	if (has_colors() == FALSE) {
		endwin();
		perror("Error: Color not supported\n");
		exit(1);
	}
	start_color();         // Enable color
	use_default_colors();  // Use default background colors
	cbreak();              // No line buffering (no Enter needed)
	noecho();              // Don't echo typed keys
	keypad(stdscr, TRUE);  // Arrow keys become KEY_UP, KEY_DOWN, ...
	nodelay(stdscr, TRUE); // getch() returns ERR if no input
	init_pair(1, COLOR_WHITE, -1);
	init_pair(2, COLOR_RED, -1);
	init_pair(3, COLOR_GREEN, -1);
	init_pair(4, COLOR_RED, COLOR_WHITE);
}

Terminal::~Terminal(void) {
	endwin();
}

void Terminal::getTerminalSize(int *cols, int *rows) {
	int x, y;
	getmaxyx(stdscr, y, x);
	*cols = x - MARGIN*2;
	*rows = y - 2;
}
