#include "Player.h"

Command Player::getCommand() noexcept {
	if (_kbhit()) {
		c = _getch();

		if (c == 'w') {
			return CHANGE_SHAPE;
		} else if (c == 's') {
			return MOVE_DOWN;
		} else if (c == 'a') {
			return MOVE_LEFT;
		} else if (c == 'd') {
			return MOVE_RIGHT;
		}
	}

	return NU;
}
