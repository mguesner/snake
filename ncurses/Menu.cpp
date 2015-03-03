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
		clear();
		getmaxyx(stdscr, y, x);
		if (ch == 'w')
			choice  = (choice - 1) < 0 ? NBMODE + 1 + (choice - 1) : (choice - 1);
		else if (ch == '\n')
			break;
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
	return (gameMode)choice;
}

std::string Menu::Name()
{
	curs_set(1);
	echo();
	clear();
	mvprintw((y / 2)  - 1, (x / 3), "enter player name : ");
	char str[9];
	while (getnstr(str, 8) == KEY_RESIZE)
	{
		getmaxyx(stdscr, y, x);
		clear();
		mvprintw((y / 2)  - 1, (x / 3), "enter player name : ");
	}
	curs_set(0);
	noecho();
	return std::string(str);
}

Menu::~Menu()
{
}

