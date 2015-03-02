#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "../Data.hpp"
#include "loader.hpp"
#include "Game.hpp"

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cout << "Usage ./nibbler width height (4 min and 1000 max)" << std::endl;
		return (EXIT_FAILURE);
	}
	std::list<int> snake(50);
	std::list<int> obj(50);
	std::string current("libcurses.so");
	loader	*graphiclib = new loader("libcurses.so", 50, 50,&snake, &obj);
	Data	*gameData = graphiclib->GetData();
	Game	*game = new Game(gameData, graphiclib, current, &snake, &obj, 50, 50);
	game->Launch();
	int value = 1;

}
