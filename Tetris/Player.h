#pragma once

#include <Windows.h>
#include <conio.h>

enum Command {
	NU, MOVE_RIGHT, MOVE_LEFT, CHANGE_SHAPE, MOVE_DOWN
};

class Player {
public:
	Command getCommand() noexcept;
private:
	int score = 0;
	char c = 0;
};

