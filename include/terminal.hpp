#pragma once

class Terminal {
public:
	Terminal(void);
	~Terminal(void);

	Terminal(const Terminal&) = delete;
	Terminal& operator=(const Terminal&) = delete;

	void getTerminalSize(int *cols, int *rows);
};
