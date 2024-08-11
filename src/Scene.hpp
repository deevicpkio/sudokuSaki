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

    Rectangle boardRect;
    Rectangle selValueRect;
    Vector2 selValuePos;
    Vector2 selValueLabelPos;

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

    Color textColor; // base text color
    Color userInputColor; // user input text color
    Color pencilMarkColor;
    int fontSize; // base font size
    int pencilMarkFontSize; // (0.1 .. n) proportional to base size (ie.: .90 means 90% of fontSize)
    int userInputFontSize;
    int menuButtonFontSize;

    float textAlignHCenter; 
    float textAlignVCenter;

	std::vector<Rectangle> buttonRecs;
} tSceneTheme;

typedef struct
{
    int index;
    tBoardCoord loc;
    std::array<tBoardCellValue, BOARD_SIZE> pencilMarks;
    bool isFixed;
    bool isSelected;
    bool isMarked;
    Rectangle cellRect;
    Vector2 valuePos;
    Vector2 pencilMarkPos;
} tScreenCell;
typedef std::array<tScreenCell, TOTAL_CELLS> tScreenBoard;

class Scene
{
public:
    Scene(int pScreenWidth, int pScreenHeight);
    ~Scene();
    void init(Board* pBoardRef);
    void draw();
    void update();
    void setSelectedValue(const tBoardCellValue pValue);
    void handleMouseAction();
    inline tBoardCellValue getSelectedValue() { return selectedValue; }

private:
    int screenWidth;
    int screenHeight;
    Board* mBoard;
    Font baseFont;
    tSceneTheme mTheme;
    tScreenBoard mBoardUI;
    tBoardCellValue selectedValue;
    Vector2 mousePos;
    int mouseBoardPos;

    void layoutSetup();
    void drawBoard();
    void drawUI();
    void drawCells();
    void drawBoxHighlight();
    void handleScreenUI();
    int getMouseBoardPosition();
    void setPencilMark(int index, tBoardCellValue pValue);
	void showSolution();
};

#endif
