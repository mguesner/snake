#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "GameObject.hpp"

class Snake : public GameObject
{
public:
	Snake(int, int);
	Snake(Snake const & src);
	Snake& operator=(Snake const & rhs);
	~Snake();
private:
	Snake();
	std::list<Point> snake;
};

#endif
