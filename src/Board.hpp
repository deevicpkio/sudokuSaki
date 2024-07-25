#ifndef SUDOKU_BOARD
#define SUDOKU_BOARD
#pragma once

typedef unsigned short tBoardCellValue;
typedef struct {
	unsigned short x;
	unsigned short y;
} tBoardCoord;

class Board
{
public:
	Board();
	~Board();
	void update();

};
#endif
