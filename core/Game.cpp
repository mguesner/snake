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

Game::Game(Data* data, loader* lib, std::string cur, int width, int height, std::list<GameObject*> *obj)
{
	this->width = width;
	this->height = height;
	object = obj;
	gameData = data;
	this->lib = lib;
	cur_lib = cur;
	first = new Player();
	(void)second;

}

Game::~Game()
{
}

void	Game::Update(int value)
{
	(void)value;
}

void Game::Launch()
{
	int value = 1;
	while (value != 27)
	{
		value = gameData->GetInput();
		std::cout << value << " KEYCODE !" << std::endl;
		if (value == 'P')
		{
			gameData->pause.lock();
			gameData->pause.unlock();
			continue;
		}
		else if (value == 'f' && cur_lib != "libcurses.so")
		{
			lib->Close();
			delete lib;
			lib = new loader("libcurses.so", 50, 50, object);
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
