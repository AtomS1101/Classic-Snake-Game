#include <ncurses.h> // Get Keyboard input and provide console io
#include <string>

#include "../include/config.hpp"
#include "../include/random.hpp"
#include "../include/snake.hpp"

void Snake::setItem(int type) {
	int isOccupied = 0;
	while (!isOccupied) {
		int x = random(1, sizeX - 2);
		int y = random(1, sizeY - 2);
		if (matrix1[convIndex(x, y)] == 0) { // Empty
			matrix1[convIndex(x, y)] = type;
			isOccupied = 1;
		}
	}
}

void Snake::eat(void) {
	length++;
	for (int i=0; i<(sizeX*sizeY); i++) if (matrix1[i] >= 2) matrix1[i]++;
}

void Snake::gameOver(void) {
	attrset(COLOR_PAIR(5));
	std::string message =
		gameOverState == -1 ? "Bonk! Hit the wall." :
		gameOverState == -3 ? " You ate poison... " :
		                      "You ate yourself...";
	for (int i=0; i<6; i++) // Paint the field white
		mvprintw(sizeY / 2 - 2 + i, sizeX / 2 - 5, "                     ");
	mvprintw(sizeY / 2 - 1, sizeX / 2 - 4, "  << Game Over >>  ");
	mvprintw(sizeY / 2 + 0, sizeX / 2 - 4, message.c_str());
	mvprintw(sizeY / 2 + 1, sizeX / 2 - 4, "     Score: %d     ", length);
	mvprintw(sizeY / 2 + 2, sizeX / 2 - 4, "    ^C to quit     ");
	mvprintw(sizeY, sizeX + MARGIN + 1, ""); // Move cursor to bottom
}

Snake::Snake(int x, int y, int spd, int food) {
	actualX = x;
	actualY = y;
	sizeX = x - MARGIN*2;
	sizeY = y - 2;
	matrix0 = new int[sizeY * sizeX];
	matrix1 = new int[sizeY * sizeX];
	direction = RIGHT;
	length = LENGTH;
	gameOverState = 0;
	speed = spd;
	foodCount = food;
}

Snake::~Snake() {
	delete[] matrix0;
	delete[] matrix1;
}

void Snake::setDirection(int dir) { direction = dir; }

int Snake::getDirection(void) { return direction; }

void Snake::initMatrix(void) {
	for (int y=0; y<sizeY; y++) {
		for (int x=0; x<sizeX; x++) {
			if (y == 0 || y == sizeY - 1 || x == 0 || x == sizeX - 1) {
				matrix1[convIndex(x, y)] = -1; // Wall
			} else {
				matrix1[convIndex(x, y)] = 0;
			}
		}
	}
	headX = sizeX / 2;
	headY = sizeY / 2;
	matrix1[convIndex(headX, headY)] = 1; // Snake head
	for (int i=1; i<=length-1; i++) matrix1[convIndex(headX-i, headY)] = length - i + 1; // Body
	for (int i=0; i<foodCount; i++) setItem(-2); // setItem() only works on matrix1
	for (int i=0; i<POISON; i++)    setItem(-3); // Set poison
	shift(); // Initialize matrix1 and shift it into matrix0
}

void Snake::show(void){
	erase();
	attrset(COLOR_PAIR(1));
	for (int i=0; i<actualX; i++) {
		for (int j=0; j<actualY; j++) {
			mvaddch(j, i, ' ');
		}
	}
	attrset(COLOR_PAIR(2));
	mvprintw(0, 0, "Score: %d", length);
	attrset(COLOR_PAIR(1));
	mvprintw(0, 12, "Speed: %d   Screen Size: %dx%d", speed, sizeX, sizeY);
	for (int y=0; y<sizeY; y++) {
		for (int x=0; x<sizeX; x++) {
			int status = matrix0[convIndex(x, y)];
			// mvprintw(y + 1, x + MARGIN, "%d", status); // For debugging
			char character =
				status == -1 ? '#' : // Wall
				status == -2 ? '*' : // Food
				status == -3 ? 'X' : // Poison
				status ==  1 ? '@' : // Head
				status >=  2 ? 'o' : // Body
				' '; // Empty
			int colorId =
				status == -1 ? 1 : // Wall
				status == -2 ? 2 : // Food
				status == -3 ? 4 : // Poison
				3; // Body
			attrset(COLOR_PAIR(colorId));
			mvaddch(y + 1, x + MARGIN, character);
		}
	}
	if (gameOverState) gameOver();
	refresh();
}

void Snake::move(void) {
	if (gameOverState) return;
	int findFood = 0;
	for (int y=0; y<sizeY; y++) {
		for (int x=0; x<sizeX; x++) {
			int status = matrix0[convIndex(x, y)];
			if (status >= 3) { // Snake body
				matrix1[convIndex(x, y)] = status - 1;
			} else if (status == 2) { // Snake tail
				matrix1[convIndex(x, y)] = 0;
			} else if (status == 1) { // Snake head
				matrix1[convIndex(x, y)] = length;
				int nextX, nextY;
				switch (direction) {
					case UP:    nextX = x;     nextY = y - 1; break;
					case DOWN:  nextX = x;     nextY = y + 1; break;
					case LEFT:  nextX = x - 1; nextY = y;     break;
					case RIGHT: nextX = x + 1; nextY = y;     break;
					default:    nextX = x;     nextY = y;     break; // Fallback
				}
				int nextStatus = matrix0[convIndex(nextX, nextY)];
				if (nextStatus == -2) findFood = 1;
				if (nextStatus >= 2 || nextStatus == -1 || nextStatus == -3) { // Hit wall or self
					gameOverState = nextStatus; return;
				}
				matrix1[convIndex(nextX, nextY)] = 1;
			} else {
				if (matrix1[convIndex(x, y)] == 1) continue; // Occupied by head
				matrix1[convIndex(x, y)] = status;
			}
		}
	}
	if (findFood) {
		eat(); // Call this after the all scanning
		setItem(-2);
		if (!random(0, 2)) { // Replace poison
			for (int i=0; i<(sizeX*sizeY); i++) if (matrix1[i] == -3) matrix1[i] = 0; // Clear poison
			for (int i=0; i<POISON; i++) setItem(-3);
		}
	}
}

void Snake::shift(void) {
	if (gameOverState) return; // Keep field when dead
	for (int i=0; i<sizeX*sizeY; i++) matrix0[i] = matrix1[i];
	delete[] matrix1;
	matrix1 = new int[sizeX * sizeY];
	for (int i=0; i<sizeX*sizeY; i++) matrix1[i] = 0; // Clear matrix1
}
