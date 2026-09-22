#pragma once

class Keyboard {
private:
	int direction; // Start with right
public:
	Keyboard(void);
	int getKey(int lastDirection);
};
