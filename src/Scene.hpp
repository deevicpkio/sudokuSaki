#ifndef SUDOKU_SCENE
#define SUDOKU_SCENE
#pragma once
#include <raylib.h>
#include "Board.hpp"

class Scene
{
public:
	Scene(int pScreenWidth, int pScreenHeight);
	~Scene();
	void init(Board* pBoardRef);
	void draw();
	void update(const tBoardData pBoardData);

private:
	int screenWidth;
	int screenHeight;
	Board* mBoard;
    Font regularFont;
};

#endif
