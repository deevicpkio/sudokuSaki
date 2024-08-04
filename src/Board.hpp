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
	tBoardCellValue value;
	tBoardCellValue solutionValue;
	bool isFixed;
	bool isWrong;
	tBoardCoord cellBoardPos;
} tBoardCell;
typedef std::array<tBoardCell, TOTAL_CELLS> tBoardData;
typedef std::array<tBoardCellValue, TOTAL_CELLS> tBoardRawData;
typedef uint_least32_t tRNGseed;

class Board
{
public:
	Board();
	~Board();
	void newBoard();
	void generatePuzzle();
	int getCellIndex(const tBoardCoord loc);
	tBoardCell getCellData(tBoardCoord pLoc);
	inline tRNGseed getSeed() { return rngSeed; }
	bool setCellPencilMark(tBoardCellValue pValue, tBoardCoord pLoc);
	bool setCellValue(tBoardCellValue pValue, tBoardCoord pLoc);

	void testPrintBoard();
	void testValuePicker();

private:
	tBoardData mBoard;
	std::array<tBoardCellValue, BOARD_SIZE> valuePicker = {1,2,3,4,5,6,7,8,9};
	tRNGseed rngSeed;
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
