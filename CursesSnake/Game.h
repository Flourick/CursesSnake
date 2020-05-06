#ifndef GAME_H
#define GAME_H

#if defined(WIN32) || defined(_WIN32)
  #include "PDCurses/curses.h"
#else
  #include <ncurses.h>
#endif

#include <chrono>
#include <string>
#include <thread>

#include "SnakePlayer.h"
#include "Food.h"

#define FOOD_COLOR_PAIR 1
#define SNAKE_HEAD_COLOR_PAIR 2
#define DEAD_SNAKE_COLOR_PAIR 3

class Game
{
private:
	int rown, coln;
	bool running = false;

	float fpsCap;
	float curFPS;

	SnakePlayer* snake;
	Food* food;

	double elapsedTimeHolder = 0.0;
	double elapsedTimeThreshold; // a.k.a. game speed

	std::chrono::system_clock::time_point beg = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

public:
	Game(int rows, int cols, float fpsCap = 60.0f, float gameSpeed = 250.0f);

	~Game();

	void start();

private:
	// called every frame, aka draw
	void update();

	// called every frame after the snake crashes
	void updateCrashed();

	// called every elapsedTimeThreshold ms
	void fixedUpdate();

	void handleInput();

	void initColors();

	void drawSnake();

	void drawFood();

	void limitFPS(float waitTime);
};

#endif // GAME_H