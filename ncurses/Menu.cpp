#include "Menu.hpp"
#include <ncurses.h>


Menu::Menu(int x, int y): x(x), y(y)
{
}

gameMode Menu::Display()
{
	int choice = 0;
	for (int i = 0; i < NBMODE + 1; ++i)
	{
		if (i == choice)
			attron(COLOR_PAIR(SELECTED));
		else
			attron(COLOR_PAIR(NORMAL));
		mvprintw((y / 2) - (NBMODE - i * 2), x / 2 - menu[i].size() / 2, menu[i].c_str());
	}
	refresh();
	int ch;
	while ((ch = getch()))
	{
		if (ch == 'w')
			choice  = (choice - 1) < 0 ? NBMODE + 1 + (choice - 1) : (choice - 1);
		else if (ch == '\n')
			return (gameMode)choice;
		for (int i = 0; i < NBMODE + 1; ++i)
		{
			if (i == choice)
				attron(COLOR_PAIR(SELECTED));
			else
				attron(COLOR_PAIR(NORMAL));
			mvprintw((y / 2) - (NBMODE - i * 2), x / 2 - menu[i].size() / 2, menu[i].c_str());
		}
	refresh();
	}
}

Menu::~Menu()
{
}

