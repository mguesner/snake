#include "Snake.hpp"

Snake::Snake()
{
	Point test(25,25,0);
	type = SNAKE;
	collider = true;
	snake.push_front(test);
}

Snake::Snake(int width , int height)
{
	bool isVertical = (rand() % 2) == 0;
	xMax = width;
	yMax = height;
	Point test(width / 2, height / 2 ,0);
	collider = true;
	type = SNAKE;
	snake.push_front(test);
	position = test;
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
	up = Point(0, -1, 0);
	down = Point(0, 1, 0);
	left = Point(-1, 0, 0);
	right = Point(1, 0, 0);
}

Snake::Snake(Snake const & src)
{
	snake = src.snake;
	current_dir = src.current_dir;
	up = src.up;
	down = src.down;
	right = src.right;
	left = src.left;
	direction = src.direction;
	speed = src.speed;
	position = src.position;
}

Snake& Snake::operator=(Snake const & src)
{
	snake = src.snake;
	current_dir = src.current_dir;
	up = src.up;
	down = src.down;
	right = src.right;
	left = src.left;
	direction = src.direction;
	speed = src.speed;
	position = src.position;
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
		++current;
		if (current == last)
			break;
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

bool	Snake::Move(bool wall)
{
	Point test = snake.front();
	Point add = test + direction;
	if (!wall)
	{
		if (add.getX() == xMax)
			add.UpdateX(0);
		else if (add.getY() == yMax)
			add.UpdateY(0);
		else if (add.getX() == -1)
			add.SetX(xMax - 1);
		else if (add.getY() == -1)
			add.SetY(yMax -1);
	}
	else
	{
		int x = add.getX();
		int y = add.getY();
		if (x == xMax || x == -1 || y == yMax || y == -1)
			return true;
	}
	position = add;
	snake.push_front(add);
	return false;
}

void	Snake::Collision()
{
	;
}

Point Snake::GetDirection()
{
	return direction;
}

void	Snake::Back()
{
	snake.pop_back();
}

std::list<Point> Snake::GetSnake()
{
	return snake;
}
