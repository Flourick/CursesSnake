#ifndef UTILS_H
#define UTILS_H

#include <random>

enum Direction
{
	UP, DOWN, LEFT, RIGHT
};

int generateNumber(int from, int to);

bool checkBounds(int rown, int coln, int rowPos, int colPos, int negg = 0);

bool checkPairInVec(std::vector<std::pair<int, int>> vec, int first, int second);

#endif // UTILS_H