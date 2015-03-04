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
	virtual	bool IsColliding() = 0;
	virtual ~GameObject();
	bool IsPhysical();
protected:

	Point position;
	ObjectType type;
	int test;
	bool	collider;
};

#endif
