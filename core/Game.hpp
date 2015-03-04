#ifndef GAME_HPP
#define GAME_HPP

#include "loader.hpp"
#include "Player.hpp"
#include "../Data.hpp"
#include "Food.hpp"

class Game
{
public:
	Game();
	Game(Data*, loader*, std::string, int , int , std::list<GameObject*>*);
	Game(Game const & src);
	Game& operator=(Game const & rhs);
	void Update(eInput value);
	~Game();
	void Launch();
private:
	int width;
	int height;
	Data *gameData;
	loader *lib;
	std::string cur_lib;
	std::list<GameObject*> *object;
	Player *first;
	Player *second;
	Food *food;
};

#endif
