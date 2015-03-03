#ifndef MENU_HPP
#define MENU_HPP

#include "Data.hpp"

#define NORMAL 1
#define SELECTED 2
#define BACKGROUND 3
#define SNAKEHEAD 4
#define SNAKEBODY 5
#define FOOD 6

class Menu
{
public:
	Menu(int, int);
	gameMode Display();
	std::string Name();
	~Menu();

private:
	int x;
	int y;
	std::string menu[NBMODE + 1] = {"new game", "quit"};
};

#endif
