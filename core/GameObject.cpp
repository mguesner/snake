#include "GameObject.hpp"

GameObject::GameObject()
{
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

