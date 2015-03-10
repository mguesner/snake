#ifndef GAME_HPP
#define GAME_HPP

#include "loader.hpp"
#include "Player.hpp"
#include "../Data.hpp"
#include "Food.hpp"
#include <thread>

class Game
{
public:
	Game(Data*, loader*, std::string, int , int , std::list<GameObject*>*);
	Game(Game const & src);
	Game& operator=(Game const & rhs);
	void Update(eInput value);
	void MainMenu(eInput value);
	void PauseMenu(eInput value);
	void EndMenu(eInput value);
	void Reset();
	ObjectType Collide();
	~Game();
	void Launch();
	void Logic();
private:
	Game();
	bool shouldLeave;
	bool wall;
	int progress;
	int score;
	int entry;
	int width;
	int height;
	std::thread core;
	eGameState state;
	Data *gameData;
	loader *lib;
	std::mutex libIsLoading;
	std::list<GameObject*> *object;
	Player *first;
	Player *second;
	Food *food;
	eInput value;
};

#endif
