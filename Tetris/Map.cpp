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

	//����
	if (dropInterval.isTimeOut()) {
		currRow++; //������һ���������

		if (currRow + currBlock->getBottomMargin() == 20) { //�䵽�ײ�
			produceNewBlock();
			return;
		}

		//���������������
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (currBlock->shape[currBlock->getCurrShape()][i][j] == 1
					&& map[currRow + i][currCol + j] == -1) {
					produceNewBlock();
					return;
				}
			}
		}

		//����
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
	currBlock->changeShape(); //������Ըı�

	//���������������
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (currBlock->shape[currBlock->getCurrShape()][i][j] == 1
				&& map[currRow + i][currCol + j] == -1) {
				currBlock->changeToLastShape();
				return;
			}
		}
	}
	//�������ǽ��(�ұ�ǽ��)
	if (currBlock->getRightMargin() + currCol >= 10) {
		currBlock->changeToLastShape();
		return;
	}

	//��������ײ�
	if (currRow + currBlock->getBottomMargin() >= 20) { //�䵽�ײ�
		currBlock->changeToLastShape();
		return;
	}

	//�ı�
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
	currRow--; //��Ϊ��show������++��һ��
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

	//���˷������º��ܷ�÷�
	checkForGetScore();
}

void Map::moveRight() {
	currCol++; //��������ƶ�

	//���������������
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (currBlock->shape[currBlock->getCurrShape()][i][j] == 1
				&& map[currRow + i][currCol + j] == -1) {
				currCol--;
				return;
			}
		}
	}
	//�������ǽ��
	if (currBlock->getRightMargin() + currCol == 10) {
		currCol--;
		return;
	}
	currCol--;
	clearOld();
	currCol++;
}

void Map::moveLeft() {
	currCol--; //��������ƶ�

	//���������������
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (currBlock->shape[currBlock->getCurrShape()][i][j] == 1
				&& map[currRow + i][currCol + j] == -1) {
				currCol++;
				return;
			}
		}
	}
	//�������ǽ��
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
	//�������Ͽ�ʼ���
	int count = 0; //��ȥ�Ĳ���
	bool isClear = true;

	for (int i = ROWS - 1; i >= 0; i--) {
		isClear = true;
		for (int j = 0; j < COLS; j++) {
			if (map[i][j] == 0) { //��һ������0����������δ������
				isClear = false;
				break;
			}
		}
		if (isClear) {
			//���������
			for (int j = 0; j < COLS; j++) {
				map[i][j] = 0;
			}
			//���Ϸ��ķ������Ʋ�ȫ�հ�
			for (int m = i; m >= 0; m--) {
				for (int n = 0; n < COLS; n++) {
					if (map[m][n] == -1) {
						map[m + 1][n] = -1;
						map[m][n] = 0;
					}
				}
			}
			i++; //�ٴ�ɨ������
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
