#include "Snake.hpp"

Snake::Snake()
{
	Point test(25,25,0);
	type = SNAKE;
	collider = true;
	snake.push_back(test);
}

Snake::Snake(int width , int height)
{
	bool isVertical = (rand() % 2) == 0;
	Point test(width / 2, height / 2 ,0);
	collider = true;
	type = SNAKE;
	snake.push_back(test);
	if (isVertical)
	{
		Point test2(width / 2,  height / 2 + 1 ,0);
		Point test3(width / 2,  height / 2 + 2 ,0);
		Point test4(width / 2,  height / 2 + 3 ,0);
		snake.push_back(test2);
		snake.push_back(test3);
		snake.push_back(test4);
		direction = Point(0, -1, 0);
		current_dir = UP;
	}
	else
	{
		Point test2(width / 2 - 1,  height / 2, 0);
		Point test3(width / 2 - 2,  height / 2, 0);
		Point test4(width / 2 - 3,  height / 2, 0);
		snake.push_back(test2);
		snake.push_back(test3);
		snake.push_back(test4);
		direction = Point(1, 0, 0);
		current_dir = RIGHT;
	}
	up = Point(0, 1, 0);
	down = Point(0, -1, 0);
	left = Point(-1, 0, 0);
	right = Point(1, 0, 0);
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

bool Snake::IsColliding()
{
	if (!snake.size())
		return false;
	auto first = snake.begin();
	auto current = snake.begin();
	auto last = snake.end();

	while (current != last)
	{
		current++;
		if (*first == *current)
			return true;
	}
	return false;
}

void Snake::SetSpeed(int value)
{
	speed = value;
}

void Snake::SetDirection(eInput dir)
{
	if (dir == LEFT && current_dir != RIGHT)
	{
		direction = left;
		current_dir = dir;
	}
	else if (dir == RIGHT && current_dir != LEFT)
	{
		direction = right;
		current_dir = dir;
	}
	else if (dir == UP && current_dir != DOWN)
	{
		direction = up;
		current_dir = dir;
	}
	else if (dir == DOWN && current_dir != UP)
	{
		direction = down;
		current_dir = dir;
	}
}

void	Snake::Move()
{
	snake.pop_back();
	Point add = snake.front() + direction;
	snake.push_front(add);
}

Point Snake::GetDirection()
{
	return direction;
}

std::list<Point> Snake::GetSnake()
{
	return snake;
}
