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
	shouldLeave = false;
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
	// if (snk->IsColliding())
	// 	shouldLeave = true;//game stat = loose
	// if snk collide food move food add point

}

void Game::Launch()
{
	eInput value = NONE;
	state = NM;
	gameData->Lock();
	gameData->SetState(state);
	while (!shouldLeave)
	{
		timeval time;
		 gettimeofday(&time, NULL);
		auto start = time.tv_usec;
		value = gameData->GetInput();
		if (value != NONE)
		{
			if (value == PAUSE)
			{
				if (state == NM)
					state = PAUSEMENU;
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
		if (state == NM)
			Update(value);
		gameData->SetState(state);
		gameData->Draw();
		gameData->Lock();
		gettimeofday(&time, NULL);
		auto wait = start + 25 - time.tv_usec;
		if (wait > 0)
			usleep(wait);
	}
	lib->Close();
	delete lib;
}
