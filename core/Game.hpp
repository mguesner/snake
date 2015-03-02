#ifndef GAME_HPP
#define GAME_HPP

class Game
{
public:
	Game();
	Game(Game const & src);
	Game& operator=(Game const & rhs);
	~Game();
};

#endif
