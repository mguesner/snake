#include "Food.hpp"

Food::Food(int width, int height)
{
	xMax = width;
	yMax = height;
	int x = rand() % xMax;
	int y = rand() % yMax;
	position = Point(x, y, 0);
}

Food::Food()
{
	;
}

Food::Food(Food const & src)
{
	(void)src;
}

Food& Food::operator=(Food const & src)
{
	(void)src;
	return *this;
}

Food::~Food()
{
}

bool Food::IsColliding()
{
	return false;
}