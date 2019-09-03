#include "Map.h"

Map::Map() {
	memset(map, 0, sizeof(map));
	currRow = 0;
	currCol = 5;

	currBlock = new Block;
	nextBlock = new Block;

	dropInterval.setDifTime(500);
}

void Map::showMapBoard() {
	setlinecolor(GREEN);
	rectangle(MAP_X, MAP_Y, MAP_X + GAMING_WIDTH, MAP_Y + GAMING_HEIGHT);
}

void Map::showMap() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (currBlock->shape[currBlock->getCurrShape()][i][j] == 1) {
				map[currRow + i][currCol + j] = 1;
			}
		}
	}

	for (int i = 0; i < COLS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (map[j][i] == 1 || map[j][i] == -1) {
				setfillcolor(WHITE);
				solidrectangle(MAP_X + i * BLOCK_SIZE + 2, MAP_Y + j * BLOCK_SIZE + 2,
					MAP_X + i * BLOCK_SIZE + BLOCK_SIZE, MAP_Y + j * BLOCK_SIZE + BLOCK_SIZE);
			} else if (map[j][i] == 0) {
				setfillcolor(getbkcolor());
				solidrectangle(MAP_X + i * BLOCK_SIZE + 2, MAP_Y + j * BLOCK_SIZE + 2,
					MAP_X + i * BLOCK_SIZE + BLOCK_SIZE, MAP_Y + j * BLOCK_SIZE + BLOCK_SIZE);
			}
		}
	}

	//下落
	if (dropInterval.isTimeOut()) {
		currRow++; //假设下一秒可以下落

		if (currRow + currBlock->getBottomMargin() == 20) { //落到底部
			produceNewBlock();
			return;
		}

		//检查碰到其他方块
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (currBlock->shape[currBlock->getCurrShape()][i][j] == 1
					&& map[currRow + i][currCol + j] == -1) {
					produceNewBlock();
					return;
				}
			}
		}

		//下落
		currRow--;
		clearOld();
		currRow++;
	}

}

void Map::processingCommand(Command command) {
	switch (command) {
	case NU:
		break;
	case MOVE_RIGHT:
		moveRight();
		break;
	case MOVE_LEFT:
		moveLeft();
		break;
	case CHANGE_SHAPE:
		checkForChange();
		break;
	case MOVE_DOWN:
		moveDown();
		break;
	default:
		break;
	}
}

void Map::checkForChange() {
	currBlock->changeShape(); //假设可以改变

	//检测碰到其他方块
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (currBlock->shape[currBlock->getCurrShape()][i][j] == 1
				&& map[currRow + i][currCol + j] == -1) {
				currBlock->changeToLastShape();
				return;
			}
		}
	}
	//检测碰到墙壁(右边墙壁)
	if (currBlock->getRightMargin() + currCol >= 10) {
		currBlock->changeToLastShape();
		return;
	}

	//检测碰到底部
	if (currRow + currBlock->getBottomMargin() >= 20) { //落到底部
		currBlock->changeToLastShape();
		return;
	}

	//改变
	currBlock->changeToLastShape();
	clearOld();
	currBlock->changeShape();
}

void Map::clearOld() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (currBlock->shape[currBlock->getCurrShape()][i][j] == 1) {
				map[currRow + i][currCol + j] = 0;
			}
		}
	}
}

void Map::produceNewBlock() {
	currRow--; //因为在show函数中++了一次
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (currBlock->shape[currBlock->getCurrShape()][i][j] == 1) {
				map[currRow + i][currCol + j] = -1;
			}
		}
	}

	delete currBlock;
	currBlock = nextBlock;
	nextBlock = new Block;

	currRow = 0;
	currCol = 5;

	//检查此方块落下后能否得分
	checkForGetScore();
}

void Map::moveRight() {
	currCol++; //假设可以移动

	//检测碰到其他方块
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (currBlock->shape[currBlock->getCurrShape()][i][j] == 1
				&& map[currRow + i][currCol + j] == -1) {
				currCol--;
				return;
			}
		}
	}
	//检测碰到墙壁
	if (currBlock->getRightMargin() + currCol == 10) {
		currCol--;
		return;
	}
	currCol--;
	clearOld();
	currCol++;
}

void Map::moveLeft() {
	currCol--; //假设可以移动

	//检测碰到其他方块
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (currBlock->shape[currBlock->getCurrShape()][i][j] == 1
				&& map[currRow + i][currCol + j] == -1) {
				currCol++;
				return;
			}
		}
	}
	//检测碰到墙壁
	if (currCol == -1) {
		currCol++;
		return;
	}
	currCol++;
	clearOld();
	currCol--;
}

void Map::moveDown() {
	clearOld();
	while (!isTouchDown()) {
		currRow++;
	}
	produceNewBlock();
}

bool Map::isTouchDown() {
	int botton = currBlock->getBottomMargin();
	for (int i = 0; i < 5; i++) {
		if (currBlock->shape[currBlock->getCurrShape()][botton][i] == 1
			&& map[currRow + botton][currCol + i] != 0) {
			return true;
		}

		if (currRow + botton >= 20) {
			return true;
		}
	}
	return false;
}

void Map::checkForGetScore() {
	//从下往上开始检查
	int count = 0; //消去的层数
	bool isClear = true;

	for (int i = ROWS - 1; i >= 0; i--) {
		isClear = true;
		for (int j = 0; j < COLS; j++) {
			if (map[i][j] == 0) { //有一个等于0，则代表改行未被消除
				isClear = false;
				break;
			}
		}
		if (isClear) {
			//将该行清除
			for (int j = 0; j < COLS; j++) {
				map[i][j] = 0;
			}
			//将上方的方块下移补全空白
			for (int m = i; m >= 0; m--) {
				for (int n = 0; n < COLS; n++) {
					if (map[m][n] == -1) {
						map[m + 1][n] = -1;
						map[m][n] = 0;
					}
				}
			}
			i++; //再次扫描这行
			count++;
		}
	}

}

bool Map::isGameOver() {
	for (int i = 0; i < 10; i++) {
		if (map[0][i] == -1) {
			return true;
		}
	}
	return false;
}
