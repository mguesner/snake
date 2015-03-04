#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "GameObject.hpp"

class Snake : public GameObject
{
public:
	Snake(int, int);
	Snake(Snake const & src);
	Snake& operator=(Snake const & rhs);
	bool IsColliding();
	void SetDirection(eInput);
	Point GetDirection();
	void SetSpeed(int);
	void	Move();
	~Snake();
private:
	Snake();
	std::list<Point> snake;
	eInput current_dir;
	Point up;
	Point down;
	Point left;
	Point right;
	Point direction;
	int speed;
};

#endif
