#include "Food.hpp"

Food::Food(int width, int height)
{
	xMax = width;
	yMax = height;
	type = FOOD;
	int x = rand() % xMax;
	int y = rand() % yMax;
	position = Point(x, y, 0);
}

Food::Food()
{
	xMax = 16;
	yMax = 16;
	type = FOOD;
	int x = rand() % xMax;
	int y = rand() % yMax;
	position = Point(x, y, 0);
}

Food::Food(Food const & src)
{
	position = src.position;
	type = src.type;
	collider = src.collider;
}

Food& Food::operator=(Food const & src)
{
	position = src.position;
	type = src.type;
	collider = src.collider;
	return *this;
}

Food::~Food()
{
}

bool Food::IsColliding()
{
	return false;
}

void Food::Collision()
{
	int x = rand() % xMax;
	int y = rand() % yMax;
	position = Point(x, y, 0);
}