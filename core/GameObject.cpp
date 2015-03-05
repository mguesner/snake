#include "GameObject.hpp"

GameObject::GameObject()
{
	collider = false;
}

GameObject::GameObject(GameObject const & src)
{
	position = src.position;
	type = src.type;
	collider = src.collider;
}

GameObject& GameObject::operator=(GameObject const & src)
{
	position = src.position;
	type = src.type;
	collider = src.collider;
	return *this;
}

GameObject::~GameObject()
{
}

bool GameObject::IsPhysical()
{
	return collider;
}

ObjectType GameObject::GetType()
{
	return type;
}
