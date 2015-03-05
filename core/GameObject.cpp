#include "GameObject.hpp"

GameObject::GameObject()
{
	collider = false;
}

GameObject::GameObject(GameObject const & src)
{
	(void)src;
}

GameObject& GameObject::operator=(GameObject const & src)
{
	(void)src;
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
