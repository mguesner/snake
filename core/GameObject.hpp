#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Point.hpp"
#include <Data.hpp>

class GameObject
{
public:
	GameObject();
	GameObject(GameObject const & src);
	GameObject& operator=(GameObject const & rhs);
	~GameObject();

private:
	Point position;
	ObjectType type;
};

#endif
