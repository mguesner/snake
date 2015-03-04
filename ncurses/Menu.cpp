#include "Menu.hpp"
#include <ncurses.h>


Menu::Menu(int x, int y): x(x), y(y)
{
}

eGameMode Menu::Display()
{
	int choice = 0;
	attron(COLOR_PAIR(NORMAL));
	mvprintw((y / 2) - (NBMODE + 9), x / 2 - 20, " _______ __    _ _______ ___   _ _______");
	mvprintw((y / 2) - (NBMODE + 8), x / 2 - 20, "|  _____|  |  | |   _   |   |_| |    ___|");
	mvprintw((y / 2) - (NBMODE + 7), x / 2 - 20, "| |_____|   |_| |  |_|  |      _|   |___");
	mvprintw((y / 2) - (NBMODE + 6), x / 2 - 20, "|_____  |  _    |       |     |_|    ___|");
	mvprintw((y / 2) - (NBMODE + 5), x / 2 - 20, " _____| | | |   |   _   |    _  |   |___");
	mvprintw((y / 2) - (NBMODE + 4), x / 2 - 20, "|_______|_|  |__|__| |__|___| |_|_______|");
	for (int i = 0; i < NBMODE; ++i)
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
		attron(COLOR_PAIR(NORMAL));
		mvprintw((y / 2) - (NBMODE + 9), x / 2 - 20, " _______ __    _ _______ ___   _ _______");
		mvprintw((y / 2) - (NBMODE + 8), x / 2 - 20, "|  _____|  |  | |   _   |   |_| |    ___|");
		mvprintw((y / 2) - (NBMODE + 7), x / 2 - 20, "| |_____|   |_| |  |_|  |      _|   |___");
		mvprintw((y / 2) - (NBMODE + 6), x / 2 - 20, "|_____  |  _    |       |     |_|    ___|");
		mvprintw((y / 2) - (NBMODE + 5), x / 2 - 20, " _____| | | |   |   _   |    _  |   |___");
		mvprintw((y / 2) - (NBMODE + 4), x / 2 - 20, "|_______|_|  |__|__| |__|___| |_|_______|");
		if (ch == 'w')
			choice  = (choice - 1) < 0 ? NBMODE + (choice - 1) : (choice - 1);
		else if (ch == '\n')
			break;
		for (int i = 0; i < NBMODE; ++i)
		{
			if (i == choice)
				attron(COLOR_PAIR(SELECTED));
			else
				attron(COLOR_PAIR(NORMAL));
			mvprintw((y / 2) - (NBMODE - i * 2), x / 2 - menu[i].size() / 2, menu[i].c_str());
		}
		refresh();
	}
	return (eGameMode)choice;
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

eActionPause Menu::Pause()
{
	int choice = 0;

	clear();
	attron(COLOR_PAIR(NORMAL));
	mvprintw((y / 2) - (NBACTIONPAUSE + 9), x / 2 - 20, " _______ _______ __   __ _______ _______ ");
	mvprintw((y / 2) - (NBACTIONPAUSE + 8), x / 2 - 20, "|    _  |   _   |  | |  |  _____|    ___|");
	mvprintw((y / 2) - (NBACTIONPAUSE + 7), x / 2 - 20, "|   |_| |  |_|  |  | |  | |_____|   |___ ");
	mvprintw((y / 2) - (NBACTIONPAUSE + 6), x / 2 - 20, "|    ___|       |  |_|  |_____  |    ___|");
	mvprintw((y / 2) - (NBACTIONPAUSE + 5), x / 2 - 20, "|   |   |   _   |       |_____| |   |___ ");
	mvprintw((y / 2) - (NBACTIONPAUSE + 4), x / 2 - 20, "|___|   |__| |__|_______|_______|_______|");
	for (int i = 0; i < NBACTIONPAUSE; ++i)
	{
		if (i == choice)
			attron(COLOR_PAIR(SELECTED));
		else
			attron(COLOR_PAIR(NORMAL));
		mvprintw((y / 2) - (NBACTIONPAUSE - i * 2), x / 2 - pause[i].size() / 2, pause[i].c_str());
	}
	refresh();
	int ch;
	while ((ch = getch()))
	{
		clear();
		getmaxyx(stdscr, y, x);
		attron(COLOR_PAIR(NORMAL));
		mvprintw((y / 2) - (NBACTIONPAUSE + 9), x / 2 - 20, " _______ _______ __   __ _______ _______ ");
		mvprintw((y / 2) - (NBACTIONPAUSE + 8), x / 2 - 20, "|    _  |   _   |  | |  |  _____|    ___|");
		mvprintw((y / 2) - (NBACTIONPAUSE + 7), x / 2 - 20, "|   |_| |  |_|  |  | |  | |_____|   |___ ");
		mvprintw((y / 2) - (NBACTIONPAUSE + 6), x / 2 - 20, "|    ___|       |  |_|  |_____  |    ___|");
		mvprintw((y / 2) - (NBACTIONPAUSE + 5), x / 2 - 20, "|   |   |   _   |       |_____| |   |___ ");
		mvprintw((y / 2) - (NBACTIONPAUSE + 4), x / 2 - 20, "|___|   |__| |__|_______|_______|_______|");
		if (ch == 'w')
			choice  = (choice - 1) < 0 ? NBACTIONPAUSE + (choice - 1) : (choice - 1);
		else if (ch == '\n')
			break;
		for (int i = 0; i < NBACTIONPAUSE; ++i)
		{
			if (i == choice)
				attron(COLOR_PAIR(SELECTED));
			else
				attron(COLOR_PAIR(NORMAL));
			mvprintw((y / 2) - (NBACTIONPAUSE - i * 2), x / 2 - pause[i].size() / 2, pause[i].c_str());
		}
		mvprintw(0, 0, "%d", choice);
		refresh();
	}
	return (eActionPause)choice;
}

void Menu::Option()
{

}

Menu::~Menu()
{
}

