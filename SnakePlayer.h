#ifndef SNAKEPLAYER_H
#define SNAKEPLAYER_H

#include <vector>
#include <algorithm>
#include <initializer_list>

#include "Player.h"
#include "utils.h"

class SnakePlayer : private Player
{
private:
	int rown, coln;
	unsigned int length;

	Direction lastMoveDir;
	Direction dir;

public:
	std::vector<std::pair<int, int>> history;

	SnakePlayer(int rown, int coln);

	void move();

	void grow();

	Direction getDirection();

	void setDirection(Direction d);

	int getHeadRow();

	int getHeadCol();

	int getLength();

private:
	void makeInitDirection();
};

#endif // SNAKEPLAYER_H