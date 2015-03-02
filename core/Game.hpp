#ifndef GAME_HPP
#define GAME_HPP

#include "loader.hpp"

class Game
{
public:
	Game();
	Game(Data*, loader*, std::string, std::list<int> *, std::list<int> *, int , int);
	Game(Game const & src);
	Game& operator=(Game const & rhs);
	void Update(int value);
	~Game();
	void Launch();
private:
	int width;
	int height;
	Data *gameData;
	loader *lib;
	std::string cur_lib;
	std::list<int> *snake;
	std::list<int> *object;
	int x_direction;
	int y_direction;
};

#endif
