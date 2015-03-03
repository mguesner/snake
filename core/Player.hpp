#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Point.hpp"
#include "Snake.hpp"

class Player
{
public:
	Player();
	Player(int nb);
	Player(Player const & src);
	Player& operator=(Player const & rhs);
	~Player();
private:
	int  nb;
	Snake *snake;
	Point direction;
	int		speed;
};

#endif
