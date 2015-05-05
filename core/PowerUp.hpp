#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "GameObject.hpp"

class PowerUp : public GameObject
{
public:
	PowerUp();
	PowerUp(int , int);
	PowerUp(PowerUp const & src);
	PowerUp& operator=(PowerUp const & rhs);
	void Collision(std::list<GameObject*> *object);
	void Collision(std::list<GameObject*> *object, Point newFood);
	bool IsColliding();
	bool IsActivate();
	void Activate();
	void SetPosition(Point pos);
	~PowerUp();


private:
	int time;
};

#endif
