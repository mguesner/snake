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
	food = new Food(width, height);
	object->push_back(food);
	shouldLeave = false;
	entry = 0;
	(void)second;

}

Game::~Game()
{
	delete first;
	delete food;
}

ObjectType	Game::Collide()
{
	auto first = object->begin();
	auto current = object->begin();
	auto last = object->end();

	while (current != last)
	{
		current++;
		if (current == last)
			break;
		if ((*first)->GetPosition() == (*current)->GetPosition())
			return (*current)->GetType();
	}
	return VOID;
}

void	Game::Update(eInput value)
{
	if (value == PAUSE)
	{
		state = PAUSEMENU;
		return;
	}
	Snake *snk = first->GetSnake();
	if (value >= UP && value <= RIGHT)
		snk->SetDirection(value);
	if (snk->Move(wall))
		shouldLeave = true;
	if (snk->IsColliding())
		shouldLeave = true;//game stat = loose
	ObjectType ret = Collide();
	if (ret == VOID)
		snk->Back();
	else
	{
		food->Collision();
		score *= 2;
	}
}

void Game::MainMenu(eInput value)
{
	(void)value;
}

void Game::PauseMenu(eInput value)
{
	if (value == VALIDATE)
	{
		if (entry == 0)
			state = NM;
		else if (entry == 1)
			state = MAINMENU;
		else if (entry == 2)
			shouldLeave = true;
		else if (entry == 3)
			wall = !wall;
		entry = 0;
		gameData->SetChoice(0);
	}
	else if (value == UP)
	{
		if (entry == 0)
			entry = NBACTIONPAUSE -1;
		else
			entry--;
		gameData->SetChoice(entry);
	}
	else if (value == DOWN)
	{
		if (entry == NBACTIONPAUSE -1)
			entry = 0;
		else
			entry++;
		gameData->SetChoice(entry);
	}
	else if (value == PAUSE)
	{
		state = NM;
		entry = 0;
		gameData->SetChoice(0);
	}
}

void Game::Launch()
{
	eInput value = NONE;
	state = NM;
	score = 1;
	wall = true;
	gameData->SetScore(score);
	gameData->SetState(state);
	gameData->Lock();
	while (!shouldLeave)
	{
		timeval time;
		 gettimeofday(&time, NULL);
		auto start = time.tv_usec;
		value = gameData->GetInput();
		if (value == F1)
		{
			lib->Close();
			delete lib;
			lib = new loader("libcurses.so", 50, 50, object);
		}
		else if (value == F2)
		{
			lib->Close();
			delete lib;
			lib = new loader("mlx/libmlx.so", 50, 50, object);
		}
		else if (value == F3)
		{
			lib->Close();
			delete lib;
			lib = new loader("libcurses.so", 50, 50, object);
		}
		if (state == NM)
			Update(value);
		else if (state == PAUSEMENU)
			PauseMenu(value);
		else if (state == MAINMENU)
			MainMenu(value);
		gameData->SetState(state);
		gameData->SetScore(score);
		gameData->Draw();
		//gameData->CleanInput();
		gettimeofday(&time, NULL);
		auto wait = start + 100000 - time.tv_usec;
		if (wait > 0)
			usleep(wait);
	}
	lib->Close();
	delete lib;
}
