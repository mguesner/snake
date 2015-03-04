#include "Game.hpp"
#include "unistd.h"
#include <ctime>
#include <sys/time.h>

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
	object->push_front(first->GetSnake());
	food = new Food(width, height);
	object->push_back(food);
	(void)second;

}

Game::~Game()
{
}

void	Game::Update(eInput value)
{
	Snake *snk = first->GetSnake();
	if (value >= UP && value <= RIGHT)
		snk->SetDirection(value);
	snk->Move();
	if (snk->IsColliding())
		;//game stat = loose
	// if snk collide food move food add point
	
}

void Game::Launch()
{
	eInput value = NONE;
	gameData->Lock();
	while (!gameData->ShouldLeave())
	{
		timeval time;
		gettimeofday(&time, NULL);
		auto start = time.tv_usec;
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
				lib->Close();
				delete lib;
				lib = new loader("libcurses.so", 50, 50, object);
			}
			else if (value == F3)
			{
				lib->Close();
				delete lib;
				lib = new loader("libcurses.so", 50, 50, object);
			}
		}
		Update(value);
		gameData->Draw();
		gameData->Lock();
		gettimeofday(&time, NULL);
		auto end = time.tv_usec;
		usleep(start + 25 - end);
	}
	lib->Close();
	delete lib;
}
