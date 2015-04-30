#ifndef GAME_HPP
#define GAME_HPP

#include "loader.hpp"
#include "Player.hpp"
#include "../Data.hpp"
#include "../Sound.hpp"
#include "Score.hpp"
#include "Food.hpp"
#include "Multi.hpp"
#include "DataEx.hpp"
#include <thread>

class Game
{
public:
	Game(Data*, loader*, std::string, int , int , std::list<GameObject*>*);
	Game(Game const & src);
	Game& operator=(Game const & rhs);
	void Update(eInput value);
	void UpdateMulti(eInput value);
	void MultiMenu(eInput value);
	void JoinMenu(eInput value);
	void HostMenu(eInput value);
	void MainMenu(eInput value);
	void PauseMenu(eInput value);
	void EndMenu(eInput value);
	void BestEndMenu(eInput value);
	void HiScoreMenu(eInput value);
	void Reset();
	ObjectType Collide();
	~Game();
	void Launch();
	void Logic();

private:
	Game();
	Multi multi;
	bool shouldLeave;
	bool wall;
	bool isHost;
	int progress;
	int score;
	int entry;
	int width;
	int height;
	Score *hiScores;
	eGameState state;
	Data *gameData;
	loader *lib;
	std::list<GameObject*> *object;
	char player[4];
	std::string addr;
	Player *first;
	Player *second;
	Food *food;
	eInput value;
	Sound *music;
};

#endif
