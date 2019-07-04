#include "SnakePlayer.h"

SnakePlayer::SnakePlayer(int rown, int coln) : Player(rown, coln)
{
	this->rown = rown;
	this->coln = coln;

	this->length = 1;

	makeInitDirection();
	this->lastMoveDir = dir;

	//this->history.push_back(std::pair<int, int>(this->getRowPos(), this->getColPos()));
}

void SnakePlayer::move()
{
	switch(dir) {
		case UP:
			history.push_back(std::pair<int, int>(this->getRowPos(), this->getColPos()));
			lastMoveDir = UP;
			moveUp();
			break;

		case LEFT:
			history.push_back(std::pair<int, int>(this->getRowPos(), this->getColPos()));
			lastMoveDir = LEFT;
			moveLeft();
			break;

		case DOWN:
			history.push_back(std::pair<int, int>(this->getRowPos(), this->getColPos()));
			lastMoveDir = DOWN;
			moveDown();
			break;

		case RIGHT:
			history.push_back(std::pair<int, int>(this->getRowPos(), this->getColPos()));
			lastMoveDir = RIGHT;
			moveRight();
			break;
	}

	if(length <= history.size()) {
		history.erase(history.begin());
	}
}

void SnakePlayer::grow()
{
	length += 1;
}

Direction SnakePlayer::getDirection()
{
	return this->dir;
}

void SnakePlayer::setDirection(Direction d)
{
	if(length == 1) {
		this->dir = d;
	}
	else if(d == lastMoveDir) {
		return;
	}
	else {
		if(d == UP && lastMoveDir != DOWN) {
			this->dir = d;
		}
		else if(d == DOWN && lastMoveDir != UP) {
			this->dir = d;
		}
		else if(d == LEFT && lastMoveDir != RIGHT) {
			this->dir = d;
		}
		else if(d == RIGHT && lastMoveDir != LEFT) {
			this->dir = d;
		}
	}
}

int SnakePlayer::getHeadRow()
{
	return this->getRowPos();
}

int SnakePlayer::getHeadCol()
{
	return this->getColPos();
}

int SnakePlayer::getLength()
{
	return this->length;
}

void SnakePlayer::makeInitDirection()
{
	int distToUp = this->getHeadRow() - 1;
	int distToDown = rown - this->getHeadRow() - 2;
	int distToLeft = this->getHeadCol() - 1;
	int distToRight = coln - this->getHeadCol() - 2;

	int maxDist = std::max({distToUp, distToDown, distToLeft, distToRight});

	if(maxDist == distToUp) {
		dir = UP;
	}
	else if(maxDist == distToDown) {
		dir = DOWN;
	}
	else if(maxDist == distToLeft) {
		dir = LEFT;
	}
	else {
		dir = RIGHT;
	}
}