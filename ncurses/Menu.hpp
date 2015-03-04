#ifndef MENU_HPP
#define MENU_HPP

#include "NcursesData.hpp"

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
	//eGameMode Display();
	std::string Name();
	eActionPause Pause();
	void Option();
	~Menu();

private:
	int x;
	int y;
	std::string menu[NBMODE] = {"new game", "quit"};
	std::string pause[NBACTIONPAUSE] = {"continue", "restart", "exit"};
};

#endif
