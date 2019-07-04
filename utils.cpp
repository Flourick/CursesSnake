#include "utils.h"

int generateNumber(int from, int to)
{
	std::random_device rd;
	std::mt19937 eng(rd());

	std::uniform_int_distribution<> distRow(from, to);

	return distRow(eng);
}

bool checkBounds(int rown, int coln, int rowPos, int colPos, int negg)
{
	if(rowPos <  negg || rowPos > (rown - 1 - negg)){
		return false;
	}
	if(colPos <  negg || colPos > (coln - 1 - negg)){
		return false;
	}

	return true;
}

bool checkPairInVec(std::vector<std::pair<int, int>> vec, int first, int second)
{
	for(std::pair<int, int> pr : vec) {
		int f = pr.first;
		int s = pr.second;

		if(f == first && s == second) {
			return true;
		}
	}

	return false;
}