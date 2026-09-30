#pragma once

class Terminal {
private:
	int x, y;
public:
	Terminal(void);
	~Terminal(void);

	Terminal(const Terminal&) = delete;
	Terminal& operator=(const Terminal&) = delete;

	void getTerminalSize(int *cols, int *rows);
};
