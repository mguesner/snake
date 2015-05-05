#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "GameObject.hpp"

class Obstacle : public GameObject
{
public:
	Obstacle(int, int);
	void Collision(std::list<GameObject*> *object);
	void Collision(std::list<GameObject*> *object, Point newFood);
	bool IsColliding();
	void SetPosition(Point pos);
	~Obstacle();
};

#endif
