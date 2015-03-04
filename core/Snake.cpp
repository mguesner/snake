#include "Snake.hpp"

Snake::Snake()
{
	Point test(25,25,0);
	type = SNAKE;
	snake.push_back(test);
}

Snake::Snake(int width , int height)
{
	Point test(25,25,0);
	type = SNAKE;
	snake.push_back(test);
}

Snake::Snake(Snake const & src)
{
	(void)src;
}

Snake& Snake::operator=(Snake const & src)
{
	(void)src;
	return *this;
}

Snake::~Snake()
{
}

