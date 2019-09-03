#pragma once

#include "AllInclude.h"
#include "Block.h"
#include <graphics.h>
#include "Timer.h"
#include "Player.h"

class Map {
public:
	Map();
	void showMapBoard();
	void showMap();
	void processingCommand(Command command);
	void checkForChange();
	

	bool isGameOver();
private:
	Block* currBlock;
	Block* nextBlock;

	char map[ROWS][COLS];

	int currRow;
	int currCol;

	void clearOld();
	void produceNewBlock();

	void moveRight();
	void moveLeft();
	void moveDown();
	
	bool isTouchDown();
	void checkForGetScore();

	Timer dropInterval;
};

