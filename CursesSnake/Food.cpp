#include "Food.h"

Food::Food(int rown, int coln, int snakeHeadRow, int snakeHeadCol, std::vector<std::pair<int, int>> snakeHistory)
{
	this->rown = rown;
	this->coln = coln;

	renew(snakeHeadRow, snakeHeadCol, snakeHistory);
}

void Food::renew(int snakeHeadRow, int snakeHeadCol, std::vector<std::pair<int, int>> snakeHistory)
{
	newPositions();

	if((rowPos == snakeHeadRow && colPos == snakeHeadCol) || checkPairInVec(snakeHistory, rowPos, colPos)) {
		renew(snakeHeadRow, snakeHeadCol, snakeHistory);
	}
}

int Food::getRowPos()
{
	return this->rowPos;
}

int Food::getColPos()
{
	return this->colPos;
}

void Food::newPositions()
{
	rowPos = generateNumber(1, rown - 2);
	colPos = generateNumber(1, coln - 2);
}