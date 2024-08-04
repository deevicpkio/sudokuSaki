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
    int fontSize; // base font size
    float pencilMarkFontSize; // (0.1 .. n) proportional to base size (ie.: .90 means 90% of fontSize)
    float userInputFontSize;
    float menuButtonFontSize;

    float textAlignHCenter; 
    float textAlignVCenter; 
} tSceneTheme;

typedef struct
{
    tBoardCoord loc;
    std::array<tBoardCellValue, BOARD_SIZE-1> pencilMarks;
    bool isFixed;
    bool isSelected;
    bool isMarked;
    Rectangle cellRect;
    Vector2 valuePos;
    Rectangle pencilMarksRect;
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

    void layoutSetup();
    void drawBoard();
    void drawUI();
    void drawCells();
    void drawBoxHighlight();
};

#endif
