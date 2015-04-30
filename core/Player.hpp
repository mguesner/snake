#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Point.hpp"
#include "Snake.hpp"

class Player
{
public:
	Player();
	Player(int nb);
	Player(std::list<GameObject*> *obj, int, int, int);
	Player(std::list<GameObject*> *obj, int, int, Point, Point);
	Player(Player const & src);
	Snake *GetSnake();
	void SetSnake(Snake *);
	Player& operator=(Player const & rhs);
	~Player();
private:
	int  nb;
	Snake *snake;
	Point direction;
	int		speed;
	std::list<GameObject*> *object;
};

#endif
