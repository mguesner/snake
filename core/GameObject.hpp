#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Point.hpp"
#include "../Data.hpp"


class GameObject
{
public:
	GameObject();
	GameObject(GameObject const & src);
	GameObject& operator=(GameObject const & rhs);
	virtual void Collision(std::list<GameObject*> *object) = 0;
	virtual	bool IsColliding() = 0;
	virtual ~GameObject();
	bool IsPhysical();
	Point GetPosition();
	ObjectType GetType();
protected:

	Point position;
	ObjectType type;
	int xMax;
	int yMax;
	int test;
	bool	collider;
};

#endif
