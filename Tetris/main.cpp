#include <graphics.h>
#include <conio.h>
#include "AllInclude.h"
#include "Map.h"
#include "Player.h"

int main() {
	srand(static_cast<unsigned>(time(nullptr)));

	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	BeginBatchDraw();
	Map m;
	Player p;

	m.showMapBoard();


	while (!m.isGameOver()) {
		m.processingCommand(p.getCommand());
		m.showMap();
		FlushBatchDraw();
		Sleep(5);
	}


	closegraph();
	EndBatchDraw();
	return 0;
}