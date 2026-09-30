#pragma once

class Snake {
private:
	int actualX, actualY;
	int sizeX, sizeY;
	int headX, headY;
	int direction;
	int length;
	int* matrix0;
	int* matrix1;
	int gameOverState;
	int speed, foodCount;

	void setItem(int type);
	void eat(void);
	void gameOver(void);
public:
	Snake(int x, int y, int spd, int food);
	~Snake(void);

	void setDirection(int dir);
	int getDirection(void);
	void initMatrix(void);
	void show(void);
	void move(void);
	void shift(void);
};
