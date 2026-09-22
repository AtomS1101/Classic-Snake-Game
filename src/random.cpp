#include <cstdlib> // Generate random numbers

int random(int min, int max) {
	return rand() % (max - min + 1) + min;
}
