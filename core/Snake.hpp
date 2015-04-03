#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "GameObject.hpp"

class Snake : public GameObject
{
public:
	Snake(int, int);
	Snake(Snake const & src);
	Snake(int, int, int);
	Snake(int, int, Point, Point);
	Snake& operator=(Snake const & rhs);
	bool IsColliding();
	void SetDirection(eInput);
	Point GetDirection();
	std::list<Point> GetSnake();
	void SetSpeed(int);
	void Collision(std::list<GameObject*> *object);
	void	Back();
	bool	Move(bool);
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
