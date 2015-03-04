#include "Game.hpp"
#include "unistd.h"

Game::Game()
{
}

Game::Game(Game const & src)
{
	(void)src;
}

Game& Game::operator=(Game const & src)
{
	(void)src;
	return *this;
}

Game::Game(Data* data, loader* lib, std::string cur, int width, int height, std::list<GameObject*> *obj)
{
	this->width = width;
	this->height = height;
	object = obj;
	gameData = data;
	this->lib = lib;
	cur_lib = cur;
	first = new Player(object, width, height);
	(void)second;

}

Game::~Game()
{
}

void	Game::Update(eInput value)
{

}

void Game::Launch()
{
	eInput value = NONE;
	gameData->Lock();
	while (!gameData->ShouldLeave())
	{
		value = gameData->GetInput();
		if (value != NONE)
		{
			if (value == PAUSE)
			{
				gameData->Pause();
				gameData->Draw();
				continue;
			}
			else if (value == F1)
			{
				lib->Close();
				delete lib;
				lib = new loader("libcurses.so", 50, 50, object);
			}
			else if (value == F2)
			{

			}
			else if (value == F3)
			{

			}
		}
		Update(value);
		gameData->Draw();
		gameData->Lock();
		usleep(200000);
	}
	lib->Close();
	delete lib;
}
