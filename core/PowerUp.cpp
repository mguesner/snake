#include "PowerUp.hpp"
#include "Snake.hpp"

PowerUp::PowerUp()
{
}

PowerUp::PowerUp(int width, int height)
{
	time = 30;
	isActivate = false;
	xMax = width;
	yMax = height;
	type = POWERUP;
	int x = rand() % xMax;
	int y = rand() % yMax;
	position = Point(x, y, 0);
}

PowerUp::PowerUp(PowerUp const & src)
{
	position = src.position;
	type = src.type;
	collider = src.collider;
}

PowerUp& PowerUp::operator=(PowerUp const & src)
{
	position = src.position;
	type = src.type;
	collider = src.collider;
	return *this;
}

bool PowerUp::IsColliding()
{
	return false;
}

void PowerUp::Collision(std::list<GameObject*> *object, Point newPowerUp)
{
	(void)object;
	position = Point(newPowerUp);
}

void PowerUp::SetPosition(Point pos)
{
	position = pos;
}

void PowerUp::Activate()
{
	isActivate = true;
	int x = rand() % xMax;
	int y = rand() % yMax;
	position = Point(x, y, 0);
	time = 30;
}

bool PowerUp::IsActivate()
{
	if (time > 0)
		time--;
	else
		isActivate = false;
	return isActivate;
}

void PowerUp::Collision(std::list<GameObject*> *object)
{
	int x = rand() % xMax;
	int y = rand() % yMax;
	position = Point(x, y, 0);
	isActivate = false;
	time = 0;
	int j = 0;
	auto i = object->begin();
	while (i != object->end())
	{
		if (*i == this)
		{
			i++;
			continue;
		}
		if ((*i)->GetType() == SNAKE)
		{
			bool re = false;
			auto tmp = ((Snake *)(*i))->GetSnake();
			for (auto k = tmp.begin(); k != tmp.end(); ++k)
			{
				if(position == (*k))
				{
					if (j % 2)
						x = (x + 1) % xMax;
					else
						y = (y + 1) % yMax;
					position = Point(x, y, 0);
					j++;
					re = true;
					break;
				}
			}
			if (re)
				i = object->begin();
			else
				i++;
		}
		else if(position == (*i)->GetPosition())
		{
			if (j % 2)
				x = (x + 1) % xMax;
			else
				y = (y + 1) % yMax;
			position = Point(x, y, 0);
			j++;
			i = object->begin();
		}
		else
			i++;
	}
}

PowerUp::~PowerUp()
{
}

