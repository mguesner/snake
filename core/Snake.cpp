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
	Point test(width / 2, (height / 3) ,0);
	collider = true;
	type = SNAKE;
	snake.push_front(test);
	position = test;
	if (isVertical)
	{
		Point test2(width / 2,  (height / 3) + 1 ,0);
		Point test3(width / 2,  (height / 3) + 2 ,0);
		Point test4(width / 2,  (height / 3) + 3 ,0);
		snake.push_back(test2);
		snake.push_back(test3);
		snake.push_back(test4);
		direction = Point(0, -1, 0);
		current_dir = UP;
	}
	else
	{
		Point test2(width / 2 - 1,  (height / 3), 0);
		Point test3(width / 2 - 2,  (height / 3), 0);
		Point test4(width / 2 - 3,  (height / 3), 0);
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

Snake::Snake(int width , int height, int nb)
{
	bool isVertical = (rand() % 2) == 0;
	xMax = width;
	yMax = height;
	Point test(width / 2, (height / 3) * nb ,0);
	collider = true;
	type = SNAKE;
	snake.push_front(test);
	position = test;
	if (isVertical)
	{
		Point test2(width / 2,  (height / 3) * nb + 1 ,0);
		Point test3(width / 2,  (height / 3) * nb + 2 ,0);
		Point test4(width / 2,  (height / 3) * nb + 3 ,0);
		snake.push_back(test2);
		snake.push_back(test3);
		snake.push_back(test4);
		direction = Point(0, -1, 0);
		current_dir = UP;
	}
	else
	{
		Point test2(width / 2 - 1,  (height / 3) * nb, 0);
		Point test3(width / 2 - 2,  (height / 3) * nb, 0);
		Point test4(width / 2 - 3,  (height / 3) * nb, 0);
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

Snake::Snake(int width , int height, Point ori, Point dir)
{
	xMax = width;
	yMax = height;
	Point test(ori);
	collider = true;
	type = SNAKE;
	snake.push_front(test);
	position = test;
	up = Point(0, -1, 0);
	down = Point(0, 1, 0);
	left = Point(-1, 0, 0);
	right = Point(1, 0, 0);
	if (dir == up)
	{
		Point test2(ori.getX(), ori.getY() + 1 ,0);
		Point test3(ori.getX(), ori.getY() + 2 ,0);
		Point test4(ori.getX(), ori.getY() + 3 ,0);
		snake.push_back(test2);
		snake.push_back(test3);
		snake.push_back(test4);
		direction = Point(0, -1, 0);
		current_dir = UP;
	}
	else
	{
		Point test2(ori.getX() - 1, ori.getY(), 0);
		Point test3(ori.getX() - 2, ori.getY(), 0);
		Point test4(ori.getX() - 3, ori.getY(), 0);
		snake.push_back(test2);
		snake.push_back(test3);
		snake.push_back(test4);
		direction = Point(1, 0, 0);
		current_dir = RIGHT;
	}
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

void Snake::AutoPLayer()
{
	Point test = snake.front();
	Point testRight = test + right;
	Point testLeft = test + left;
	Point testDown = test + down;
	Point testUp = test + up;
}

void	Snake::Collision(std::list<GameObject*> *object)
{
	(void)object;
}

Point Snake::GetDirection()
{
	return direction;
}

void	Snake::Back()
{
	snake.pop_back();
}

void	Snake::SetSnake(std::list<Point> toSave)
{
	snake = toSave;
}

std::list<Point> Snake::GetSnake()
{
	return snake;
}
