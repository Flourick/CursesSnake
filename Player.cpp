#include "Player.h"

Player::Player(int rown, int coln)
{
	this->rown = rown;
	this->coln = coln;

	generatePosition();
}

void Player::moveUp()
{
	rowPos -= 1;
}

void Player::moveDown()
{
	rowPos += 1;
}

void Player::moveLeft()
{
	colPos -= 1;
}

void Player::moveRight()
{
	colPos += 1;
}

int Player::getRowPos()
{
	return rowPos;
}

int Player::getColPos()
{
	return colPos;
}

void Player::generatePosition()
{
	rowPos = generateNumber(1, rown - 2);
	colPos = generateNumber(1, coln - 2);
}