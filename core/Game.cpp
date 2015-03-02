#include "Game.hpp"

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

Game::Game(Data* data, loader* lib, std::string cur, std::list<int> *snk, std::list<int> *obj, int width, int height)
{
	this->width = width;
	this->height = height;
	gameData = data;
	this->lib = lib;
	cur_lib = cur;
	snake = snk;
	object = obj;
	x_direction = 1;
	y_direction = 0;
}

Game::~Game()
{
}

void	Game::Update(int value)
{
	if (value == 1)
	{
		y_direction = 1;
		x_direction = 0;
	}
	else if (value == 2)
	{
		y_direction = 0;
		x_direction = 1;
	}
}

void Game::Launch()
{
	int value = 1;
	while (value != 27)
	{
		value = gameData->GetInput();
		std::cout << value << " KEYCODE !" << std::endl;
		if (value == 'f' && cur_lib != "libcurses.so")
		{
			lib->Close();
			delete lib;
			lib = new loader("libcurses.so", 50, 50, snake, object);
		}
		else if (value == '2' && cur_lib != "libopengl.so")
		{

		}
		else if (value == '3' && cur_lib != "lib.so")
		{

		}
		Update(value);
	}
}
