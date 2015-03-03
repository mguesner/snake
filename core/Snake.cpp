#include "Snake.hpp"

Snake::Snake()
{
	Point test(25,25,0);
	type = SNAKE;
	snake.push_back(test);
}

Snake::Snake(Snake const & src)
{
}

Snake& Snake::operator=(Snake const & rhs)
{
}

Snake::~Snake()
{
}

