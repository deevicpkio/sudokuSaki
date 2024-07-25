#pragma once
#include <raylib.h>
#include "Board.hpp"

class App {
public:
	App();
	int start();
private:
	void mainLoop();
	void handleInput();
	void update();
	void draw();

	Board* board;
};
