
#include <cstdlib>
#include <ctime>
#include <dlfcn.h>
#include "../Data.hpp"
#include "loader.hpp"
#include "Game.hpp"
#include "GameObject.hpp"

int main(int argc, char **argv)
{
	(void)argv;
	if (argc < 3)
	{
		std::cout << "Usage ./nibbler width height (4 min and 1000 max)" << std::endl;
		return (EXIT_FAILURE);
	}
	// RANDOM INITIALIZER
	srand(time(NULL));
	std::string current("libcurses.so");
	std::list<GameObject*> obj;
	loader	*graphiclib = new loader("libcurses.so", 50, 50, &obj);
	Data	*gameData = graphiclib->GetData();
	Game	*game = new Game(gameData, graphiclib, current, 50, 50, &obj);
	game->Launch();
	return (EXIT_SUCCESS);
}
