#include "Scene.hpp"
#include "Board.hpp"
#include "config.h"
#include <raylib.h>

Scene::Scene(int pScreenWidth, int pScreenHeight) : screenWidth(pScreenWidth), screenHeight(pScreenHeight)
{
    
}

void Scene::init(Board* pBoardRef)
{
    regularFont = LoadFont("assets/fonts/MesloLGS NF Regular.ttf");

    mBoard = pBoardRef;
}

void Scene::update(const tBoardData pBoardData)
{
    
}

void Scene::draw()
{
    Color boardBorderColor = {0, 0, 0, 255}; // Black
    Color boardBackgroundColor = {255, 255, 255, 255}; // White
    float boardBorderThickness = 4.0f;
    
    float boardMarginV = 40.0;
    float boardMarginH = 50.0;
    float boardWidth = SCREEN_HEIGHT*.90-boardMarginV;
    float boardHeight = SCREEN_HEIGHT*.90-boardMarginV;
    
    Color cellBorderColorDefault = {0, 0, 0, 255}; // Black
    Color cellBorderColorSelected = {10, 10, 255, 255}; // Blue
    Color cellBorderColor = cellBorderColorDefault;
    Color cellBackgroundColorDefault = {255, 255, 255, 255}; // White
    Color cellBackgroundColorFixed = {235, 235, 235, 255}; // LightGray
    Color cellBackgroundColorSelected = {245, 245, 245, 255}; // DarkGray
    Color cellBackgroundColor = cellBackgroundColorDefault;
    
    float cellBorderThickness = 1.0f;
    
    // NOTE:
    // Draw Board
    Rectangle boardRect = {boardMarginH, boardMarginV, boardWidth, boardHeight};
    //DrawRectangleRec(boardRect, boardBackgroundColor);
    DrawRectangleLinesEx(boardRect, boardBorderThickness, boardBorderColor);

    // NOTE:
    // Draw Cells
    Rectangle cellRect = {};
    float cellWidth = (boardWidth / 9.0f) - 2.0f*boardBorderThickness/9.0f;
    float cellHeight = (boardHeight / 9.0f) - 2.0f*boardBorderThickness/9.0f;
    float xPos, yPos;

    // borders
    for (int i=0;i<BOARD_SIZE;i++)
    {
        for (int j=0;j<BOARD_SIZE;j++)
        {
            xPos = boardMarginH+cellWidth*j+boardBorderThickness;
            yPos = boardMarginV+cellHeight*i+boardBorderThickness;
            cellRect = {xPos, yPos, cellWidth, cellHeight};
            DrawRectangleRec(cellRect, cellBackgroundColor);
            DrawRectangleLinesEx(cellRect, cellBorderThickness, cellBorderColor);
        }
    }
    // border highlights
    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            xPos = boardMarginH+cellWidth*j*3+boardBorderThickness;
            yPos = boardMarginV+cellHeight*i*3+boardBorderThickness;
            cellRect = {xPos, yPos, cellWidth*3, cellHeight*3};
            DrawRectangleLinesEx(cellRect, boardBorderThickness*0.75f, cellBorderColor);
        }
    }
}
