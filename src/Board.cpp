#include "Board.hpp"
#include "config.h"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <spdlog/spdlog.h>

Board::Board()
{
}

Board::~Board()
{

}

void Board::cleanBoard()
{
    spdlog::debug("ENTERED cleanBoard()");

    tCoordItem row = 0;
    tCoordItem col = 0;
    for (auto& cell : mBoard)
    {
        if (col >= BOARD_SIZE)
        {
            row++;
            col = 0;
        }

        cell.value = 0;
        cell.solutionValue = 0;
        cell.isWrong = false;
        cell.isFixed = true;
        cell.cellBoardPos.row = row;
        cell.cellBoardPos.col = col;
        col++;
    }
}

void Board::newBoard()
{
    spdlog::debug("ENTERED newBoard()");
    cleanBoard();
    // NOTE: RNG always reseeded for each new board
    initializeRNG();
    
    tBoardCoord origin = {0, 0};

    if (!generateBoard(origin)) 
    {
        std::cout << "Error generating the puzzle. Wrong seed?";
        return;
    }
    
    generatePuzzle();

    SHOW_VAR_INFO(rngSeed);

    //testPrintBoard();
}

void Board::getBoardData(tBoardData* boardData)
{
    spdlog::debug("ENTERED getBoardData()");

    int index = 0;
    for (const auto& cell : mBoard)
    {
        boardData->at(index).value = cell.value;
        boardData->at(index).isFixed = cell.isFixed;
        boardData->at(index).cellBoardPos = cell.cellBoardPos;
        index++;
    }
}

void Board::getBoardDataRaw(tBoardRawData* boardRawData)
{
    spdlog::debug("ENTERED getBoardRaw()");

    int index = 0;
    for (const auto& cell : mBoard)
    {
        boardRawData->at(index) = cell.value;
        index++;
    }
}

bool Board::generateBoard(tBoardCoord pLoc)
{
    spdlog::debug("generatingBoard->cell({},{})", pLoc.row, pLoc.col);

    tBoardCoord loc = pLoc;
    int index = 0;
    // NOTE: generate with recurse backtracking
    if (loc.row == 9)
    {
        return true;

    } else if (loc.col == 9)
    {
        return generateBoard({tCoordItem(loc.row+1),0});

    } else if (!isEmpty(loc))
    {
        return generateBoard({loc.row,tCoordItem(loc.col+1)});

    } else
    {
        for (auto value : valuePicker)
        {
            if (isValidInput(value, loc))
            {
                index = getCellIndex(loc);
                spdlog::debug("Generate Board->accessing index: {}", index);
                mBoard.at(index).value = value;
                mBoard.at(index).solutionValue = value;
                if (generateBoard({loc.row,tCoordItem(loc.col+1)}))
                {
                    return true;
                }
                mBoard.at(index).value = 0;         // backtrack
                mBoard.at(index).solutionValue = 0; // backtrack
            }
        }
        return false; // could not generate puzzle?
    }
}

void Board::generatePuzzle()
{
    tBoardCellValue pick;
    for (auto& cell : mBoard)
    {
        cell.isFixed = true;
        
        pick = getRandomValue();
        if (pick < 6)
        {
            cell.value = 0;
            cell.isFixed = false;
        } else
        {
        }
    }
}

int Board::getCellIndex(const tBoardCoord loc)
{
    int index = loc.col + (loc.row * BOARD_SIZE);

    return index;
}

bool Board::isEmpty(const int index)
{
    spdlog::debug("ENTERED isEmpty({})", index);
    return mBoard.at(index).value == 0;
}

bool Board::isEmpty(const tBoardCoord cell)
{
    spdlog::debug("ENTERED isEmpty({},{})", cell.row, cell.col);
    return mBoard.at(getCellIndex(cell)).value == 0;
}

bool Board::isValidInput(const tBoardCellValue value, const tBoardCoord loc)
{
    spdlog::debug("ENTERED isValidInput({} - ({},{}))", value, loc.row, loc.col);

    int index = 0;
    // NOTE: check row
    for (tCoordItem i=0; i < BOARD_SIZE; i++)
    {
        index = getCellIndex({loc.row, i});
        spdlog::debug("isValidInput->check row {}->accessing index: {}", loc.row, index);
        if (value == mBoard.at(index).value) return false; 
    }

    // NOTE: check column
    for (tCoordItem i=0; i < BOARD_SIZE; i++)
    {
        index = getCellIndex({i,loc.col});
        spdlog::debug("isValidInput->check column {}->accessing index: {}", loc.col, index);
        if (value == mBoard.at(index).value) return false; 
    }

    // NOTE: check 3x3 block
    tCoordItem rowFrom = std::floor(loc.row/3)*3;
    tCoordItem rowTo = std::floor(loc.row/3)*3+3;
    tCoordItem colFrom = std::floor(loc.col/3)*3;
    tCoordItem colTo = std::floor(loc.col/3)*3+3;

    spdlog::debug("Checking box-> From:({},{}) To:({},{})", rowFrom, colFrom, rowTo, colTo);
    
    for (tCoordItem i=rowFrom; i < rowTo; i++)
    {
        for (tCoordItem j=colFrom; j < colTo; j++)
        {
            index = (i * BOARD_SIZE) + j;
            spdlog::debug("isValidInput->check 3x3 box->accessing index: {}", index);
            if (value == mBoard.at(index).value) return false; 
        }
    }

    return true;
}

void Board::initializeRNG()
{
    spdlog::debug("ENTERED initializeRNG()");

    std::random_device os_seed;
    rngSeed = os_seed(); // Generate Seed
    
    std::mt19937 rng(rngSeed);
    SHOW_VAR(rngSeed);

    randGen = rng;
    std::uniform_int_distribution<tBoardCellValue> distribute(1, BOARD_SIZE);
    rngDistrib = distribute;

    std::shuffle(valuePicker.begin(), valuePicker.end(), randGen);
    isRNGinitialized = true;
}

tBoardCellValue Board::getRandomValue()
{
    if (!isRNGinitialized) 
    {
        initializeRNG();
    }

    return valuePicker.at(rngDistrib(randGen)-1);
}

void Board::testPrintBoard()
{
    spdlog::debug("ENTERED testPrintBoard()");

    int index = 0;
    std::cout << "=======================================================\n|  "; // end of row
    for (const auto& cell : mBoard) 
    {
        std::cout << cell.value << "  |  ";
        if (cell.cellBoardPos.col == 8) 
        {
            std::cout << "\n";
            if (cell.cellBoardPos.row < 8)
            {
                std::cout << "|  ";
            }
        }
    }
    std::cout << "=======================================================\n"; // end of row
}

void Board::testValuePicker()
{
    std::cout << "pre : [";
    for (const auto& value : valuePicker)
    {
         std::cout << (int)value << " ";
    }
    std::cout << "]\n";

    initializeRNG();
    
    std::cout << "post: [";
    for (const auto& value : valuePicker)
    {
         std::cout << (int)value << " ";
    }
    std::cout << "]\n";

}

tBoardCell Board::getCellData(tBoardCoord pLoc)
{
    return mBoard.at(getCellIndex(pLoc));
}

// TODO: implement this
bool Board::setCellValue(tBoardCellValue pValue, tBoardCoord pLoc)
{
    int index = getCellIndex(pLoc);
    
    if (mBoard.at(index).isFixed) return false;

    if (mBoard.at(index).solutionValue != pValue) mBoard.at(index).isWrong = true;

    mBoard.at(index).value = pValue;

    return true;
}
