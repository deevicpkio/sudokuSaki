#include "Board.hpp"
#include <iostream>
#include <math.h>
#include <algorithm>

Board::Board()
{
}

Board::~Board()
{

}

void Board::update()
{

}

void Board::cleanBoard()
{
    for (int col = 0; col < BOARD_SIZE; col++)
    {
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            mBoard[row][col].value = 0;
            mBoard[row][col].isFixed = false;
            mBoard[row][col].pencilMarks.fill(0);
            mBoard[row][col].cellBoardPos.row = row+1;
            mBoard[row][col].cellBoardPos.col = col+1;
        }

    }
}

void Board::newBoard()
{
    cleanBoard();
    // NOTE: RNG always reseeded for each new board
    initializeRNG();

    generateBoard();

    testPrintBoard();
}

void Board::getBoardData(tBoardData* boardData)
{
    int n = sizeof(mBoard) / sizeof(mBoard[0][0]);
    std::copy(mBoard, mBoard + n, *boardData);
}

void Board::generateBoard()
{
    // NOTE: generate with recurse backtracking
    for (tCoordItem row = 0; row < BOARD_SIZE; row++)
    {
        for (tCoordItem col = 0; col < BOARD_SIZE; col++)
        {
            if (!isEmpty({row,col}))
            {
                getRandomValue();
            }
        }
    }
}

bool Board::isEmpty(const tBoardCoord cell)
{
    return mBoard[cell.row][cell.col].value == 0;
}

bool Board::isValidInput(const tBoardCellValue value, const tCoordItem row, const tCoordItem col)
{
    // NOTE: check row
    for (tCoordItem i=0; i < BOARD_SIZE; i++)
    {
        if (value == mBoard[row][i].value) return false; 
    }

    // NOTE: check column
    for (tCoordItem i=0; i < BOARD_SIZE; i++)
    {
        if (value == mBoard[i][col].value) return false; 
    }

    // NOTE: check 3x3 block
    tCoordItem rowFrom = std::floor(row/3)*3;
    tCoordItem rowTo = std::floor(row/3)*3+3;
    tCoordItem colFrom = std::floor(col/3)*3;
    tCoordItem colTo = std::floor(col/3)*3+3;
    
    for (tCoordItem i=rowFrom; i < rowTo; i++)
    {
        for (tCoordItem j=colFrom; j < colTo; j++)
        {
            if (value == mBoard[i][j].value) return false; 
        }
    }

    return true;
}

void Board::initializeRNG()
{
    std::random_device os_seed;
    rngSeed = os_seed(); // Generate Seed
    std::mt19937 rng(rngSeed);

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
    for (tCoordItem row = 0; row < BOARD_SIZE; row++)
    {
        std::cout << "=========================\n"; // end of row
        for (tCoordItem  col = 0; col < BOARD_SIZE; col++)
        {
            std::string fixed = mBoard[row][col].isFixed ? "*" : "";
            std::cout << fixed << mBoard[row][col].value << fixed;
            std::cout << "(";
            for (auto mark : mBoard[row][col].pencilMarks )
            {
                std::cout << mark; 
            }
            std::cout << ")"; 
            std::cout << "-(row:" << mBoard[row][col].cellBoardPos.row;
            std::cout << "/col:" << mBoard[row][col].cellBoardPos.col << ")\n";
        }
    }
    std::cout << "=========================\n"; // end of row
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
