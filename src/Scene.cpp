#include "Scene.hpp"
#include "Board.hpp"
#include "config.h"
#include <raylib.h>
#include <spdlog/spdlog.h>
#include <string>

Scene::Scene(int pScreenWidth, int pScreenHeight) : screenWidth(pScreenWidth), screenHeight(pScreenHeight)
{
    regularFont = LoadFont("assets/fonts/MesloLGS NF Regular.ttf");

    mTheme.boardBorderColor = {0, 0, 0, 255}; // Black
    mTheme.boardBackgroundColor = {255, 255, 255, 255}; // White
    mTheme.boardBorderThickness = 4.0f;

    mTheme.boardMarginH = 50.0f;
    mTheme.boardMarginV = 40.0f;
    mTheme.boardWidth = screenHeight*.90-mTheme.boardMarginH;
    mTheme.boardHeight = screenHeight*.90-mTheme.boardMarginV;
    mTheme.cellMarginV = mTheme.boardMarginV + mTheme.boardBorderThickness;
    mTheme.cellMarginH = mTheme.boardMarginH + mTheme.boardBorderThickness;

    mTheme.cellBorderColorDefault = {0, 0, 0, 255}; // Black
    mTheme.cellBorderColorSelected = {10, 10, 255, 255}; // Blue
    mTheme.cellBorderColor = mTheme.cellBorderColorDefault;
    mTheme.cellBackgroundColorDefault = {255, 255, 255, 255}; // White
    mTheme.cellBackgroundColorFixed = {235, 235, 235, 255}; // LightGray
    mTheme.cellBackgroundColorSelected = {245, 245, 245, 255}; // DarkGray
    mTheme.cellBackgroundColor = mTheme.cellBackgroundColorDefault;

    mTheme.cellBorderThickness = 1.0f;
    mTheme.cellWidth = (mTheme.boardWidth / 9.0f) - ((2.0f * mTheme.boardBorderThickness) / 9.0f);
    mTheme.cellHeight = (mTheme.boardHeight / 9.0f) - ((2.0f * mTheme.boardBorderThickness) / 9.0f);

    mTheme.textColor = {0, 0, 0, 255}; // Black 
    mTheme.textAlignHCenter = (mTheme.cellWidth / 2.0f) - (regularFont.recs->width / 2.0f); 
    mTheme.textAlignVCenter = (mTheme.cellHeight / 2.0f) - (regularFont.recs->height / 2.0f); 

    SHOW_VAR(mTheme.cellWidth)
    SHOW_VAR(mTheme.cellHeight)
    SHOW_VAR(mTheme.cellMarginH)
    SHOW_VAR(mTheme.cellMarginV)
    SHOW_VAR(mTheme.textAlignHCenter)
    SHOW_VAR(mTheme.textAlignVCenter)
    
}

void Scene::init(Board* pBoardRef)
{

    mBoard = pBoardRef;
}

void Scene::update(const tBoardData pBoardData)
{
    
}

void Scene::draw()
{
    Rectangle boardRect = {mTheme.boardMarginH, mTheme.boardMarginV, mTheme.boardWidth, mTheme.boardHeight};
    Rectangle cellRect = {};
    float xPos, yPos;

    // NOTE:
    // Draw Board
    DrawRectangleLinesEx(boardRect, mTheme.boardBorderThickness, mTheme.boardBorderColor);

    // NOTE:
    // Draw Cells

    // borders
    for (int i=0;i<BOARD_SIZE;i++)
    {
        for (int j=0;j<BOARD_SIZE;j++)
        {
            xPos = (mTheme.cellWidth * j) + mTheme.cellMarginH;
            yPos = (mTheme.cellHeight * i) + mTheme.cellMarginV;
            cellRect = {xPos, yPos, mTheme.cellWidth, mTheme.cellHeight};
            DrawRectangleRec(cellRect, mTheme.cellBackgroundColor);
            DrawRectangleLinesEx(cellRect, mTheme.cellBorderThickness, mTheme.cellBorderColor);
        }
    }
    // border highlights
    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            xPos = (mTheme.cellWidth * j * 3) + mTheme.cellMarginH;
            yPos = (mTheme.cellHeight * i * 3) + mTheme.cellMarginV;
            cellRect = {xPos, yPos, mTheme.cellWidth*3, mTheme.cellHeight*3};
            DrawRectangleLinesEx(cellRect, mTheme.boardBorderThickness*0.75f, mTheme.cellBorderColor);
        }
    }

    // TODO: text rendering
    int index = 0;
    tBoardCell cell;
    Vector2 pos;

    for (tCoordItem i=0;i<BOARD_SIZE;i++)
    {
        for (tCoordItem j=0;j<BOARD_SIZE;j++)
        {
            cell = mBoard->getCellData({i,j});
            pos.x = (mTheme.cellWidth * j) + mTheme.cellMarginH + mTheme.textAlignHCenter;
            pos.y = (mTheme.cellHeight * i) + mTheme.cellMarginV + mTheme.textAlignVCenter;

            DrawTextEx(regularFont, std::to_string(cell.value).c_str(), pos, 36.0f, 0.0f, mTheme.textColor);
        }
    }
}
