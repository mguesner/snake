#include "Player.hpp"

Player::Player()
{
	nb = 1;
	snake = new Snake();
	speed = 1;
}

Player::Player(int nb)
{
	this->nb = nb;
	snake = new Snake();
	speed = 1;
}

Player::Player(std::list<GameObject*> *obj, int width, int height)
{
	nb = 1;
	snake = new Snake(width , height);
	speed = 1;
	obj->push_front(snake);
}

Player::Player(Player const & src)
{
	(void)src;
}

Player& Player::operator=(Player const & src)
{
	(void)src;
	return *this;
}

Player::~Player()
{
	delete snake;
}

