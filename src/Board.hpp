#ifndef SUDOKU_BOARD
#define SUDOKU_BOARD
#pragma once
#include <cstdint>
#include <array>
#include <random>

#define BOARD_SIZE 9
#define TOTAL_CELLS BOARD_SIZE*BOARD_SIZE

typedef unsigned short tBoardCellValue;
typedef unsigned short tCoordItem;
typedef struct {
	tCoordItem row;
	tCoordItem col;
} tBoardCoord;
typedef struct {
	float x;
	float y;
} tScreenCoord;
typedef struct {
	tBoardCellValue value;
	bool isFixed;
	std::array<tBoardCellValue, BOARD_SIZE-1> pencilMarks;
	tBoardCoord cellBoardPos;
	//tScreenCoord cellScreenPos;
} tBoardCell;
typedef std::array<tBoardCell, TOTAL_CELLS> tBoardData;
typedef std::array<tBoardCellValue, TOTAL_CELLS> tBoardRawData;


class Board
{
public:
	Board();
	~Board();
	void update();
	void newBoard();
	int getCellIndex(const tBoardCoord loc);
	tBoardCell getCellData(tBoardCoord pLoc);
	bool setCellPencilMark(tBoardCellValue pValue, tBoardCoord pLoc);
	bool setCellValue(tBoardCellValue pValue, tBoardCoord pLoc);

	void testPrintBoard();
	void testValuePicker();

private:
	tBoardData mBoard;
	std::array<tBoardCellValue, BOARD_SIZE> valuePicker = {1,2,3,4,5,6,7,8,9};
	uint_least32_t rngSeed;
	bool isRNGinitialized = false;
	std::uniform_int_distribution<tBoardCellValue> rngDistrib;
	std::mt19937 randGen;

	void cleanBoard();
	bool generateBoard(tBoardCoord pLoc);
	bool isEmpty(const tBoardCoord cell);
	bool isValidInput(const tBoardCellValue value, const tBoardCoord loc);
	void initializeRNG();
	tBoardCellValue getRandomValue();
	void getBoardData(tBoardData* boardData);
	void getBoardDataRaw(tBoardRawData* boardRawData);

};
#endif
