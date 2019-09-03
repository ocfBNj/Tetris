#include "BLOCK.h"

#include <iostream>
#include <array>

Block::Block() noexcept {
	memset(shape, 0, sizeof(shape));
	type = static_cast<BlockType>(rand() % 2);
	currShape = 0;

	switch (type) {
	case I:
		/*
			10000
			10000
			10000
			10000
			00000
		*/
		shape[0][0][0] = 1;
		shape[0][1][0] = 1;
		shape[0][2][0] = 1;
		shape[0][3][0] = 1;

		shape[2][0][0] = 1;
		shape[2][1][0] = 1;
		shape[2][2][0] = 1;
		shape[2][3][0] = 1;

		shape[1][0][0] = 1;
		shape[1][0][1] = 1;
		shape[1][0][2] = 1;
		shape[1][0][3] = 1;

		shape[3][0][0] = 1;
		shape[3][0][1] = 1;
		shape[3][0][2] = 1;
		shape[3][0][3] = 1;

		break;
	case J:
		/*
			10000
			11100
			00000
			00000
			00000
		*/

		shape[0][0][0] = 1;
		shape[0][1][0] = 1;
		shape[0][1][1] = 1;
		shape[0][1][2] = 1;

		/*
			01000
			01000
			11000
			00000
			00000
		*/

		shape[1][0][1] = 1;
		shape[1][1][1] = 1;
		shape[1][2][0] = 1;
		shape[1][2][1] = 1;

		/*
			10000
			11100
			00000
			00000
			00000
		*/

		shape[2][0][0] = 1;
		shape[2][1][0] = 1;
		shape[2][1][1] = 1;
		shape[2][1][2] = 1;

		/*
			11000
			10000
			10000
			00000
			00000
		*/

		shape[3][0][0] = 1;
		shape[3][0][1] = 1;
		shape[3][1][0] = 1;
		shape[3][2][0] = 1;

		break;
	case L:
		break;
	case O:
		break;
	case S:
		break;
	case Z:
		break;
	case T:
		break;
	default:
		break;
	}
}

void Block::changeShape() noexcept {
	currShape++;
	if (currShape >= 4) {
		currShape = 0;
	}
}

void Block::changeToLastShape() noexcept {
	if (currShape == 0) {
		currShape = 3;
	} else {
		currShape--;
	}

}

char Block::getBottomMargin() noexcept {
	for (int i = 4; i >= 0; i--) {
		for (int j = 0; j < 5; j++) {
			if (shape[currShape][i][j] == 1) {
				return i;
			}
		}
	}

	return 0;
}

char Block::getLeftMargin() noexcept {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {

			if (shape[currShape][j][i] == 1) {
				return i;
			}
		}
	}
	return 0;
}

char Block::getRightMargin() noexcept {
	for (int i = 4; i >= 0; i--) {
		for (int j = 0; j < 5; j++) {
			if (shape[currShape][j][i] == 1) {
				return i;
			}
		}
	}
	return 0;
}
