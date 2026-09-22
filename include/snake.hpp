#pragma once

class Snake {
private:
	int sizeX, sizeY;
	int headX, headY;
	int direction;
	int length;
	int* matrix0;
	int* matrix1;
	int isAlive;

	void setFood(void);
	void eat(void);
public:
	Snake(int x, int y);
	~Snake(void);

	void setDirection(int dir);
	int getDirection(void);
	void initMatrix(void);
	void show(void);
	void move(void);
	void shift(void);
};
