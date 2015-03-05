#ifndef MENU_HPP
#define MENU_HPP

#include "NcursesData.hpp"



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
