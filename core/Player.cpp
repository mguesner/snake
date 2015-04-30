#include "Player.hpp"

Player::Player()
{
	nb = 1;
	snake = new Snake(4, 4);
	speed = 1;
}

Player::Player(int nb)
{
	this->nb = nb;
	snake = new Snake(4, 4);
	speed = 1;
}

Player::Player(std::list<GameObject*> *obj, int width, int height, int nb) : nb(nb)
{
	//nb = 1;
	snake = new Snake(width, height, nb);
	speed = 1;
	obj->push_front(snake);
	object = obj;
}

Player::Player(std::list<GameObject*> *obj, int width, int height, Point ori, Point dir)
{
	snake = new Snake(width, height, ori, dir);
	obj->push_front(snake);
	object = obj;
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

void Player::SetSnake(Snake *replace)
{
	object->remove(snake);
	delete snake;
	snake = replace;
	object->push_front(snake);
}

Snake *Player::GetSnake()
{
	return snake;
}
