#pragma once

#include "AllInclude.h"
#include <cstdlib>
#include <memory>

enum BlockType {
	I, J, L, O, S, Z, T
};

class Block {
public:
	Block() noexcept;

	char getCurrShape() noexcept { return currShape; }
	void changeShape() noexcept;
	void changeToLastShape() noexcept;

	char shape[4][5][5];

	char getBottomMargin() noexcept;
	char getLeftMargin() noexcept; //”–Œ Ã‚
	char getRightMargin() noexcept;


private:
	BlockType type;

	char currShape;
};

