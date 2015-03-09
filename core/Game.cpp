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
	progress = 200000;
	entry = 0;
	(void)second;

}

Game::~Game()
{
	delete first;
	delete food;
}

void	Game::Reset()
{
	score = 0;
	object->erase(object->begin(), object->end());
	delete first;
	delete food;
	first = new Player(object, width, height);
	food = new Food(width, height);
	object->push_back(food);
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
	{
		//shouldLeave = true;
		state = ENDMENU;
	}
	if (snk->IsColliding())
	{
		//shouldLeave = true;//game stat = loose
		state = ENDMENU;
	}
	ObjectType ret = Collide();
	if (ret == VOID)
		snk->Back();
	else
	{
		food->Collision();
		score += 1;
	}
}

void Game::MainMenu(eInput value)
{
	if (value == VALIDATE)
	{
		if (entry == 0)
			state = NM;
		else if (entry == 1)
			wall = !wall;
		else if (entry == 2)
		{
			shouldLeave = true;
		}
	}
	else if (value == UP)
	{
		if (entry == 0)
			entry = NBMODE -1;
		else
			entry--;
	}
	else if (value == DOWN)
	{
		if (entry == NBMODE -1)
			entry = 0;
		else
			entry++;
	}
	else if (value == PAUSE)
	{
		state = NM;
		entry = 0;
	}
	gameData->SetChoice(entry);
}

void Game::PauseMenu(eInput value)
{
	if (value == VALIDATE)
	{
		if (entry == 0)
			state = NM;
		else if (entry == 1)
		{
			Reset();
			state = NM;
		}
		else if (entry == 2)
			shouldLeave = true;
		// else if (entry == 3)
		// 	wall = !wall;
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

void Game::EndMenu(eInput value)
{
	if (value == VALIDATE)
	{
		if (entry == 0)
		{
			Reset();
			state = NM;
		}
		else if (entry == 1)
		{
			Reset();
			state = MAINMENU;
		}
		else if (entry == 2)
			shouldLeave = true;
		entry = 0;
		gameData->SetChoice(0);
	}
	else if (value == UP)
	{
		if (entry == 0)
			entry = NBACTIONEND - 1;
		else
			entry--;
		gameData->SetChoice(entry);
	}
	else if (value == DOWN)
	{
		if (entry == NBACTIONEND - 1)
			entry = 0;
		else
			entry++;
		gameData->SetChoice(entry);
	}
	else if (value == PAUSE)
	{
		shouldLeave = true;
	}
}

void Game::Launch()
{
	eInput value = NONE;
	state = MAINMENU;
	score = 0;
	wall = true;
	gameData->SetScore(score);
	gameData->SetState(state);
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
		else if (state == ENDMENU)
			EndMenu(value);
		gameData->SetState(state);
		gameData->SetScore(score);
		gameData->SetWall(wall);
		gameData->Draw();
		//gameData->CleanInput();
		gettimeofday(&time, NULL);
		auto wait = start + progress - time.tv_usec;
		if (wait > 0)
			usleep(wait);
	}
	lib->Close();
	delete lib;
}
