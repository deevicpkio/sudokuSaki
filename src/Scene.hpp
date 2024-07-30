#ifndef SUDOKU_SCENE
#define SUDOKU_SCENE
#pragma once

#include "Board.hpp"

class Scene
{
public:
	Scene(int pScreenWidth, int pScreenHeight);
	~Scene();
	void init(const tBoardData pBoardData);
	void draw();
	void update(const tBoardData pBoardData);

private:
	int screenWidth;
	int screenHeight;
	tBoardData mBoardData;

};

#endif
