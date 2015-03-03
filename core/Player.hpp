#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player
{
public:
	Player();
	Player(Player const & src);
	Player& operator=(Player const & rhs);
	~Player();
};

#endif
