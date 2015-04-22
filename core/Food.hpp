#ifndef FOOD_HPP
#define FOOD_HPP

#include "GameObject.hpp"

class Food : public GameObject
{
public:
	Food(int, int);
	Food(Food const & src);
	Food& operator=(Food const & rhs);
	void Collision(std::list<GameObject*> *object);
	void Collision(std::list<GameObject*> *object, Point newFood);
	bool IsColliding();
	~Food();
private:
	Food();
};

#endif
