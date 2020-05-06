#include "Game.h"

Game::Game(int rows, int cols, float fpsCap, float gameSpeed)
{
	this->rown = rows;
	this->coln = cols;

	this->fpsCap = fpsCap;
	this->curFPS = fpsCap;

	this->elapsedTimeThreshold = gameSpeed;

	initColors();

	this->snake = new SnakePlayer(rown, coln);
	this->food = new Food(rown, coln, snake->getHeadRow(), snake->getHeadCol(), snake->history);
}

Game::~Game()
{
	delete snake;
	delete food;
}

void Game::start()
{
	running = true;

	// game
	while(running) {
		limitFPS(1000.f / fpsCap);

		handleInput();

		if(elapsedTimeHolder >= elapsedTimeThreshold) {
			float overflow = elapsedTimeHolder - elapsedTimeThreshold;
			fixedUpdate();
			elapsedTimeHolder = overflow;
		}

		erase(); // clears the screen
		update();
		refresh();
	}

	// snake disappearance
	float thresh = 1800.0f / snake->history.size();

	while(snake->history.size() != 0) {
		limitFPS(1000.f / fpsCap);

		if(elapsedTimeHolder >= thresh) {
			float overflow = elapsedTimeHolder - thresh;

			snake->history.erase(snake->history.end() - 1);

			elapsedTimeHolder = overflow;
		}

		erase(); // clears the screen
		updateCrashed();
		refresh();
	}
}

void Game::update()
{
	border(0, 0, 0, 0, 0, 0, 0, 0);
	//mvprintw(0, 0, "FPS: %.1f", curFPS);
	mvprintw(0, 0, "SCORE: %d", snake->getLength() - 1);

	drawFood();
	drawSnake();
}

void Game::updateCrashed()
{
	border(0, 0, 0, 0, 0, 0, 0, 0);
	//mvprintw(0, 0, "FPS: %.1f", curFPS);
	mvprintw(0, 0, "SCORE: %d", snake->getLength() - 1);

	drawFood();

	// draw snake body
	for(unsigned int i = 0; i < snake->history.size(); i++) {
		if(i == snake->history.size() - 1) {
			attron(COLOR_PAIR(DEAD_SNAKE_COLOR_PAIR));
			mvprintw(snake->history.at(i).first, snake->history.at(i).second, ""); addch(' ' | A_REVERSE);
			attroff(COLOR_PAIR(DEAD_SNAKE_COLOR_PAIR));
		}
		else {
			mvprintw(snake->history.at(i).first, snake->history.at(i).second, ""); addch(' ' | A_REVERSE);
		}
	}
}

void Game::fixedUpdate()
{
	snake->move();

	//check out-of-bounds
	if(!checkBounds(rown, coln, snake->getHeadRow(), snake->getHeadCol(), 1)) {
		running = false;
	}

	//check snake crashed into himself (what an idiot...)
	if(checkPairInVec(snake->history, snake->getHeadRow(), snake->getHeadCol())) {
		running = false;
	}

	// food eaten
	if(food->getColPos() == snake->getHeadCol() && food->getRowPos() == snake->getHeadRow()) {
		snake->grow();

		food->renew(snake->getHeadRow(), snake->getHeadCol(), snake->history);
	}
}

void Game::handleInput()
{
	char ch = getch();

	switch(ch) {
		case 27:
			running = false;
			break;

		case 'w':
			snake->setDirection(UP);
			break;

		case 'a':
			snake->setDirection(LEFT);
			break;

		case 's':
			snake->setDirection(DOWN);
			break;

		case 'd':
			snake->setDirection(RIGHT);
			break;
	}
}

void Game::initColors()
{
	init_pair(FOOD_COLOR_PAIR, COLOR_YELLOW, COLOR_BLACK);
	init_pair(SNAKE_HEAD_COLOR_PAIR, COLOR_CYAN, COLOR_BLACK);
	init_pair(DEAD_SNAKE_COLOR_PAIR, COLOR_RED, COLOR_BLACK);
}

void Game::drawSnake()
{
	//head
	attron(COLOR_PAIR(SNAKE_HEAD_COLOR_PAIR));
	mvprintw(snake->getHeadRow(), snake->getHeadCol(), ""); addch(' ' | A_REVERSE);
	attroff(COLOR_PAIR(SNAKE_HEAD_COLOR_PAIR));

	//body
	for(unsigned int i = 0; i < snake->history.size(); i++) {
		mvprintw(snake->history.at(i).first, snake->history.at(i).second, ""); addch(' ' | A_REVERSE);
	}
}

void Game::drawFood()
{
	attron(COLOR_PAIR(FOOD_COLOR_PAIR));
	mvprintw(food->getRowPos(), food->getColPos(), "$");
	attroff(COLOR_PAIR(FOOD_COLOR_PAIR));
}

void Game::limitFPS(float waitTime)
{
	beg = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> delta = beg - end;

	if(delta.count() < waitTime) {
		std::chrono::duration<double, std::milli> delta_ms(waitTime - delta.count());
		auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
		std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));

		elapsedTimeHolder += waitTime;
		curFPS = 1000.0f / waitTime;
	}
	else {
		elapsedTimeHolder += delta.count();
		curFPS = 1000.0f / delta.count();
	}

	end = std::chrono::system_clock::now();
}