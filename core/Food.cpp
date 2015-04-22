#include "Food.hpp"
#include "Snake.hpp"

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

void Food::Collision(std::list<GameObject*> *object, Point newFood)
{
	(void)object;
	position = Point(newFood);
	// int j = 0;
	// auto i = object->begin();
	// while (i != object->end())
	// {
	// 	if (*i == this)
	// 	{
	// 		i++;
	// 		continue;
	// 	}
	// 	if ((*i)->GetType() == SNAKE)
	// 	{
	// 		bool re = false;
	// 		auto tmp = ((Snake *)(*i))->GetSnake();
	// 		for (auto k = tmp.begin(); k != tmp.end(); ++k)
	// 		{
	// 			std::cout << "test : " << position << " -> " << (*k) << std::endl;
	// 			if(position == (*k))
	// 			{
	// 				if (j % 2)
	// 					x = (x + 1) % xMax;
	// 				else
	// 					y = (y + 1) % yMax;
	// 				position = Point(x, y, 0);
	// 				j++;
	// 				re = true;
	// 				std::cout << "nop new position " << position << std::endl;
	// 				break;
	// 			}
	// 		}
	// 		if (re)
	// 			i = object->begin();
	// 		else
	// 			i++;
	// 	}
	// 	else if(position == (*i)->GetPosition())
	// 	{
	// 		if (j % 2)
	// 			x = (x + 1) % xMax;
	// 		else
	// 			y = (y + 1) % yMax;
	// 		position = Point(x, y, 0);
	// 		j++;
	// 		i = object->begin();
	// 		std::cout << "nop2" << std::endl;
	// 	}
	// 	else
	// 		i++;
	// }
}

void Food::Collision(std::list<GameObject*> *object)
{
	int x = rand() % xMax;
	int y = rand() % yMax;
	position = Point(x, y, 0);
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
				std::cout << "test : " << position << " -> " << (*k) << std::endl;
				if(position == (*k))
				{
					if (j % 2)
						x = (x + 1) % xMax;
					else
						y = (y + 1) % yMax;
					position = Point(x, y, 0);
					j++;
					re = true;
					std::cout << "nop new position " << position << std::endl;
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
			std::cout << "nop2" << std::endl;
		}
		else
			i++;
	}
}
