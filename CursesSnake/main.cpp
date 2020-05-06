#include <stdexcept>
#include "Game.h"

int main(int argc, char* argv[])
{
	int row, col;
	int prevCursor = -1;
	float speed = 125.0f;

	if(argc > 1) {
		std::string str(argv[1]);

		try {
			speed = std::stof(str);
		}
		catch(const std::invalid_argument& ex) {
			printf("ERROR: first argument must be a number (100, 10.525 ... represents snake speed!)\n");
			return -1;
		}
	}

	initscr();
	timeout(0);
	prevCursor = curs_set(0);
	raw();
	keypad(stdscr, TRUE);
	noecho();
	getmaxyx(stdscr, row, col);

	if(row < 12 || col < 12) {
		endwin();
		printf("ERROR: terminal dimensions MUST be atleast 12-rows X 12-cols!\n");
		return -2;
	}
	else if(!has_colors())
	{
		endwin();
		printf("ERROR: color support required!\n");
		return -3;
	}
	start_color();

	Game* game;

	game = new Game(row, col, 120.0f, speed);
	game->start();

	delete game;

	if(prevCursor != -1) {
		curs_set(prevCursor);
	}
	endwin();

	return 0;
}