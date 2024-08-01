#ifndef SUDOKU_SCENE
#define SUDOKU_SCENE
#pragma once
#include <raylib.h>
#include "Board.hpp"

typedef struct 
{
    Color boardBorderColor;
    Color boardBackgroundColor;
    float boardBorderThickness;

    float boardMarginV;
    float boardMarginH;
    float boardWidth;
    float boardHeight;
    float cellMarginV;
    float cellMarginH;

    Color cellBorderColorDefault;
    Color cellBorderColorSelected;
    Color cellBorderColor;
    Color cellBackgroundColorDefault;
    Color cellBackgroundColorFixed;
    Color cellBackgroundColorSelected;
    Color cellBackgroundColor;

    float cellBorderThickness;
    float cellWidth;
    float cellHeight;

    Color textColor;
    float textAlignHCenter; 
    float textAlignVCenter; 
} tSceneTheme;

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
	tSceneTheme mTheme;
};

#endif
