#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "GameObject.hpp"

class Snake : public GameObject
{
public:
	Snake();
	Snake(Snake const & src);
	Snake& operator=(Snake const & rhs);
	~Snake();
private:
	std::list<Point> snake;
};

#endif
