#ifndef SUDOKU_APP
#define SUDOKU_APP
#pragma once
#include <raylib.h>
#include "Board.hpp"
#include "Scene.hpp"

class App {
public:
	App();
	int start();
private:
	void mainLoop();
	void handleInput();
	void update();
	void draw();

	Board* mBoard;
	Scene* mScene;
};
#endif
