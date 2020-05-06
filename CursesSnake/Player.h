#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"

class Player
{
private:
	int rown, coln;

	int rowPos, colPos;

public:
	Player(int rown, int coln);
	void moveUp();

	void moveDown();

	void moveLeft();

	void moveRight();

	int getRowPos();

	int getColPos();

private:
	void generatePosition();
};

#endif // PLAYER_H