#ifndef FOOD_H
#define FOOD_H

#include "utils.h"

class Food
{
private:
	int rown, coln;
	int rowPos, colPos;

public:
	Food(int rown, int coln, int snakeHeadRow, int snakeHeadCol, std::vector<std::pair<int, int>> snakeHistory);

	void renew(int snakeHeadRow, int snakeHeadCol, std::vector<std::pair<int, int>> snakeHistory);

	int getRowPos();
	int getColPos();

private:
	void newPositions();
};

#endif // FOOD_H