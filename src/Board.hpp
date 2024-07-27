#ifndef SUDOKU_BOARD
#define SUDOKU_BOARD
#pragma once
#include <cstdint>
#include <array>
#include <random>

#define BOARD_SIZE 9

typedef uint8_t tBoardCellValue;
typedef uint8_t tCoordItem;
typedef struct {
	uint8_t row;
	uint8_t col;
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
typedef tBoardCell tBoardData[BOARD_SIZE][BOARD_SIZE];
typedef tBoardCellValue tBoardRawData[BOARD_SIZE*BOARD_SIZE];


class Board
{
public:
	Board();
	~Board();
	void update();
	void newBoard();
	void getBoardData(tBoardData* boardData);
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
	void generateBoard();
	bool isEmpty(const tBoardCoord cell);
	bool isValidInput(const tBoardCellValue value, const tCoordItem row, const tCoordItem col);
	void initializeRNG();
	tBoardCellValue getRandomValue();

};
#endif
