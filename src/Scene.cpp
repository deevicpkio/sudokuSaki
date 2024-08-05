#include "Scene.hpp"
#include "Board.hpp"
#include "config.h"
#include <raylib.h>
#include <spdlog/spdlog.h>
#include <string>

Scene::Scene(int pScreenWidth, int pScreenHeight) : screenWidth(pScreenWidth), screenHeight(pScreenHeight)
{
}

void Scene::init(Board* pBoardRef)
{
    tBoardCell cell;
    int index;
    

    selectedValue = 0;

    mBoard = pBoardRef;
    layoutSetup();

    for (tCoordItem i=0;i<BOARD_SIZE;i++)
    {
        for (tCoordItem j=0;j<BOARD_SIZE;j++)
        {
            index = mBoard->getCellIndex({i,j});
            cell = mBoard->getCellData({i,j});
            
            mBoardUI.at(index).index = index;
            mBoardUI.at(index).loc = cell.cellBoardPos;
            mBoardUI.at(index).isFixed = cell.isFixed;
            mBoardUI.at(index).isMarked = false; 
            mBoardUI.at(index).isSelected = false; 
            mBoardUI.at(index).pencilMarks.fill(0); 

            mBoardUI.at(index).cellRect.x = (mTheme.cellWidth * j) + mTheme.cellMarginH;
            mBoardUI.at(index).cellRect.y = (mTheme.cellHeight * i) + mTheme.cellMarginV;
            mBoardUI.at(index).cellRect.width = mTheme.cellWidth;
            mBoardUI.at(index).cellRect.height = mTheme.cellHeight;

            mBoardUI.at(index).valuePos.x = (mTheme.cellWidth * j) + mTheme.cellMarginH + mTheme.textAlignHCenter;
            mBoardUI.at(index).valuePos.y = (mTheme.cellHeight * i) + mTheme.cellMarginV + mTheme.textAlignVCenter;
            
            mBoardUI.at(index).pencilMarkPos.x = (mTheme.cellWidth * j) + mTheme.cellMarginH + (baseFont.recs->width / 3.0f) ;
            mBoardUI.at(index).pencilMarkPos.y = (mTheme.cellHeight * i) + mTheme.cellMarginV + mTheme.textAlignVCenter;
        }
    }
}

void Scene::layoutSetup()
{
    mTheme.boardBorderColor = {0, 0, 0, 255}; // Black
    mTheme.boardBackgroundColor = {255, 255, 255, 255}; // White
    mTheme.boardBorderThickness = 4.0f;

    mTheme.boardMarginH = 50.0f;
    mTheme.boardMarginV = 40.0f;
    mTheme.boardWidth = screenHeight*.90-mTheme.boardMarginH;
    mTheme.boardHeight = screenHeight*.90-mTheme.boardMarginV;
    mTheme.boardRect = {mTheme.boardMarginH, mTheme.boardMarginV, mTheme.boardWidth, mTheme.boardHeight};
    
    mTheme.cellMarginV = mTheme.boardMarginV + mTheme.boardBorderThickness;
    mTheme.cellMarginH = mTheme.boardMarginH + mTheme.boardBorderThickness;

    mTheme.cellBorderColorDefault = {0, 0, 0, 255}; // Black
    mTheme.cellBorderColorSelected = {10, 10, 255, 255}; // Blue
    mTheme.cellBorderColor = mTheme.cellBorderColorDefault;
    mTheme.cellBackgroundColorDefault = {255, 255, 255, 255}; // White
    mTheme.cellBackgroundColorFixed = {124, 175, 234, 255}; // LightBlue
    mTheme.cellBackgroundColorSelected = {245, 245, 245, 255}; // DarkGray
    mTheme.cellBackgroundColor = mTheme.cellBackgroundColorDefault;

    mTheme.cellBorderThickness = 1.0f;
    mTheme.cellWidth = (mTheme.boardWidth / 9.0f) - ((2.0f * mTheme.boardBorderThickness) / 9.0f);
    mTheme.cellHeight = (mTheme.boardHeight / 9.0f) - ((2.0f * mTheme.boardBorderThickness) / 9.0f);

    mTheme.selValueRect.x = mTheme.boardRect.x + mTheme.boardRect.width + mTheme.boardMarginH;
    mTheme.selValueRect.y = mTheme.boardRect.y;
    mTheme.selValueRect.width = mTheme.cellWidth;
    mTheme.selValueRect.height = mTheme.cellHeight;
    
    mTheme.textColor = {0, 0, 0, 255}; // Black 
    mTheme.userInputColor = {10, 10, 255, 255}; // Blue
    mTheme.pencilMarkColor = {61, 61, 255, 255}; // Blue
    baseFont = LoadFontEx("assets/fonts/MesloLGS NF Regular.ttf", 48, NULL, NULL);
    mTheme.fontSize = baseFont.baseSize;
    mTheme.userInputFontSize = mTheme.fontSize * 1.0f;
    mTheme.pencilMarkFontSize = mTheme.fontSize * .5f;
    mTheme.menuButtonFontSize = mTheme.fontSize * .5f;
    mTheme.textAlignHCenter = (mTheme.cellWidth / 2.0f) - (baseFont.recs->width / 2.0f); 
    mTheme.textAlignVCenter = (mTheme.cellHeight / 2.0f) - (baseFont.recs->height / 2.0f); 
    
    mTheme.selValuePos.x = mTheme.selValueRect.x + mTheme.textAlignHCenter;
    mTheme.selValuePos.y = mTheme.selValueRect.y + mTheme.textAlignVCenter;
    mTheme.selValueLabelPos.x = mTheme.selValueRect.x + (baseFont.recs->width * .5f);
    mTheme.selValueLabelPos.y = mTheme.selValueRect.y + mTheme.selValueRect.height + 5.0f;
}

void Scene::update()
{
    handleScreenUI();
}

void Scene::handleScreenUI()
{
    int index = getMouseBoardPosition();
    if (index < 0) return;
    for (auto& cell : mBoardUI)
    {
        if (cell.index == index && !cell.isFixed)
        {
            cell.isSelected = true;
        } else
        {
            cell.isSelected = false;
        }
    }
}

int Scene::getMouseBoardPosition()
{
    Vector2 newMousePos = GetMousePosition();
    if (mousePos.x != newMousePos.x || mousePos.y != newMousePos.y)
    {
        mousePos = newMousePos;
        for (auto& cellUI : mBoardUI)
        {
            if (CheckCollisionPointRec(mousePos, cellUI.cellRect))
            {
                mouseBoardPos = cellUI.index;
                return cellUI.index;
            }
        }
    } else
    {
        return mouseBoardPos;
    }
    mouseBoardPos = -1;
    return -1;
}

void Scene::handleMouseAction()
{
    int index = getMouseBoardPosition();
    if (index < 0) return;
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        if (mBoard->isEmpty(index))
        {
            // NOTE: handle pencil marks
            setPencilMark(index, selectedValue);
        } else
        {
            // NOTE: empty cell
            mBoard->setCellValue(0, mBoardUI.at(index).loc);
        }
        
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        // NOTE: handle user value
        mBoard->setCellValue(selectedValue, mBoardUI.at(index).loc);
    }
}

void Scene::setPencilMark(int index, tBoardCellValue pValue)
{
    if (pValue == 0)
    {
        for (auto& mark : mBoardUI.at(index).pencilMarks)
        {
            mark = 0;
        }
    } else
    {
        if (mBoardUI.at(index).pencilMarks.at(pValue-1) == pValue)
        {
            mBoardUI.at(index).pencilMarks.at(pValue-1) = 0;
        } else
        {
            mBoardUI.at(index).pencilMarks.at(pValue-1) = selectedValue;
        }
    }
}

void Scene::draw()
{

    drawBoard();

    drawUI();

    drawCells();

    drawBoxHighlight();

}

void Scene::setSelectedValue(const tBoardCellValue pValue)
{
    if (pValue >= 0 && pValue <= 9 && selectedValue != pValue) 
    {
        selectedValue = pValue;
        SHOW_VAR(selectedValue)
    }
}


void Scene::drawBoard()
{
    DrawRectangleLinesEx(mTheme.boardRect, mTheme.boardBorderThickness, mTheme.boardBorderColor);
}

void Scene::drawUI()
{
    // Selected Value
    DrawRectangleRec(mTheme.selValueRect, mTheme.cellBackgroundColorDefault);
    DrawRectangleLinesEx(mTheme.selValueRect, mTheme.boardBorderThickness, mTheme.cellBorderColorDefault);
    if (selectedValue != 0)
    {
        DrawTextEx(baseFont, std::to_string(selectedValue).c_str(), mTheme.selValuePos, baseFont.baseSize, 0.0f, mTheme.userInputColor);
    }
    DrawTextEx(baseFont, "Selected", mTheme.selValueLabelPos, mTheme.menuButtonFontSize, 0.0f, mTheme.textColor);
}

void Scene::drawCells()
{
    tScreenCell cellUI;
    tBoardCell cell;
    int index;
    float cellBorderThickness, fontSize;
    Color textColor, cellBackgroundColor, cellBorderColor;

    for (tCoordItem i=0;i<BOARD_SIZE;i++)
    {
        for (tCoordItem j=0;j<BOARD_SIZE;j++)
        {
            index = mBoard->getCellIndex({i,j});
            cell = mBoard->getCellData({i,j});
            cellUI = mBoardUI.at(index);
            
            // NOTE:
            // Draw cell background
            cellBackgroundColor = mTheme.cellBackgroundColorDefault;
            if (cellUI.isFixed)
            {
                cellBackgroundColor = mTheme.cellBackgroundColorFixed;
            } else if (cellUI.isSelected)
            {
                cellBackgroundColor = mTheme.cellBackgroundColorSelected;
            }
            DrawRectangleRec(cellUI.cellRect, cellBackgroundColor);

            // NOTE:
            // Draw cell border
            if (cellUI.isSelected)
            {
                cellBorderColor = mTheme.cellBorderColorSelected;
                cellBorderThickness = mTheme.cellBorderThickness * 2.0f;
            } else
            {
                cellBorderColor = mTheme.cellBorderColor;
                cellBorderThickness = mTheme.cellBorderThickness;
            }
            DrawRectangleLinesEx(cellUI.cellRect, cellBorderThickness, cellBorderColor);
            
            // NOTE: 
            // Draw cell values
            if (cell.value != 0) 
            {
                // NOTE:
                // Draw fixed/user value
                if (cell.isFixed)
                {
                    textColor = mTheme.textColor;
                    fontSize = mTheme.fontSize;
                } else
                {
                    textColor = mTheme.userInputColor;
                    fontSize = mTheme.userInputFontSize;
                }
                DrawTextEx(baseFont, std::to_string(cell.value).c_str(), cellUI.valuePos, fontSize, 0.0f, textColor);
            } else
            {
                // NOTE:
                // Draw pencil marks
                std::string pencilMarks = ""; 
                for (const auto& mark : cellUI.pencilMarks)
                {
                    if (mark > 0)
                    {
                        pencilMarks += std::to_string(mark);
                    }
                    
                }
                DrawTextEx(baseFont, pencilMarks.c_str(), cellUI.pencilMarkPos, mTheme.pencilMarkFontSize, 0.0f, mTheme.pencilMarkColor);
            }
        }
    }
}

void Scene::drawBoxHighlight()
{
    Rectangle cellRect = {};
    float xPos, yPos;

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
}

