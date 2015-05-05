#include "Obstacle.hpp"

Obstacle::Obstacle(int width, int height)
{
	isActivate = true;
	xMax = width;
	yMax = height;
	type = OBSTACLE;
	int x = width / 2;
	int y = height / 2;
	position = Point(x, y, 0);
}

bool Obstacle::IsColliding()
{
	return false;
}

void Obstacle::Collision(std::list<GameObject*> *object)
{
	(void) object;
}

void Obstacle::SetPosition(Point pos)
{
	position = pos;
}

Obstacle::~Obstacle()
{
}

