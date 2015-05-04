
#include <cstdlib>
#include <ctime>
#include <dlfcn.h>
#include "../Data.hpp"
#include "loader.hpp"
#include "Game.hpp"
#include "GameObject.hpp"

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cout << "Usage ./nibbler width height (16min and 2billion max)" << std::endl;
		return (EXIT_FAILURE);
	}
	int height;
	int width;
	try
	{
		width = std::stoi(argv[1]);
		height = std::stoi(argv[2]);
		if (width < 16 || height < 16)
		{
			std::cout << "Usage ./nibbler width height (16 min and 2billion max)" << std::endl;
			exit(-1);
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Usage ./nibbler width height (16 min and 2billion max)" << std::endl;
		return (EXIT_FAILURE);
	}
	// RANDOM INITIALIZER
	srand(time(NULL));
	std::string current("libcurses.so");
	std::list<GameObject*> obj;
	try
	{
		// loader	*graphiclib = new loader("sdl/libsdl.so", width, height, &obj);
		loader	*graphiclib = new loader("ncurses/libcurses.so", width, height, &obj);
		// loader 	*graphiclib = new loader("sfml/libsfml.so", width, height, &obj);
		Data	*gameData = graphiclib->GetData();
		Game	*game = new Game(gameData, graphiclib, current, width, height, &obj);
		game->Launch();
		delete game;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (EXIT_SUCCESS);
}
