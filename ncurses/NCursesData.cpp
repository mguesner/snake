#include "NCursesData.hpp"
#include "Menu.hpp"
#include "../core/GameObject.hpp"
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

NCursesData::NCursesData(int width, int height, std::list<GameObject*> *objects)
{
	initscr();
	curs_set(0);
	noecho();
	start_color();
	getmaxyx(stdscr, yScreen, xScreen);
	init_pair(NORMAL, COLOR_WHITE, COLOR_BLACK);
	init_pair(SELECTED, COLOR_BLACK, COLOR_WHITE);
	init_pair(BACKGROUND, COLOR_BLACK, COLOR_WHITE);
	init_pair(SNAKEHEAD, COLOR_WHITE, COLOR_RED);
	init_pair(SNAKEBODY, COLOR_BLACK, COLOR_GREEN);
	init_pair(FOOD, COLOR_RED, COLOR_WHITE);
	funcs[(int)MAINMENU] = &NCursesData::DrawMainMenu;
	funcs[(int)NM] = &NCursesData::DrawNormalMode;
	this->width = width;
	this->height = height;
	this->objects = objects;
	shouldReset = false;
	shouldLeave = false;
	value = NONE;
	inputs['w'] = UP;
	inputs['s'] = DOWN;
	inputs['a'] = LEFT;
	inputs['d'] = RIGHT;
	inputs['p'] = PAUSE;
	inputs[80] = F1;
	inputs[81] = F2;
	inputs[82] = F3;
	inputs['\n'] = VALIDATE;
	display = std::thread(&NCursesData::StartDisplay, this);
	input = std::thread(&NCursesData::StartInput, this);
}

void NCursesData::Lock()
{
	mutex.lock();
}

void NCursesData::Draw()
{
	mutex.unlock();
}

void NCursesData::StartDisplay()
{
	while (!shouldLeave)
	{
		mutex.lock();
		mutex.unlock();
		getmaxyx(stdscr, yScreen, xScreen);
		if (yScreen < height || xScreen < (width + 15))
		{
			clear();
			attron(COLOR_PAIR(NORMAL));
			mvprintw(yScreen / 2, xScreen / 2 - 9, "please resize term");
			refresh();
			continue;
		}
		clear();
		(this->*funcs[state])();
	}
}

void NCursesData::StartInput()
{
	int ch;
	timeout(200);
	while (!shouldLeave && (ch = getch()))
	{
		value = inputs[ch];
		//mvprintw(0,0,"%d", ch);
		pause.lock();
		pause.unlock();
	}
}

eInput NCursesData::GetInput()
{
	return value;
}

bool NCursesData::ShouldLeave()
{
	return shouldLeave;
}

bool NCursesData::ShouldReset()
{
	return shouldReset;
}

void NCursesData::SetChoice(int choice)
{
	this->choice = choice;
}

void NCursesData::SetState(eGameState state)
{
	this->state = state;
}

void NCursesData::Pause()
{
	pause.lock();
	Menu menu(xScreen, yScreen);
	auto res = menu.Pause();
	if (res == EXIT2)
		shouldLeave = true;
	else if (res == RESTART)
		shouldReset = true;
	pause.unlock();
}

void NCursesData::DrawMainMenu()
{
	attron(COLOR_PAIR(NORMAL));
	mvprintw((yScreen / 2) - (NBMODE + 9), xScreen / 2 - 20, " _______ __    _ _______ ___   _ _______");
	mvprintw((yScreen / 2) - (NBMODE + 8), xScreen / 2 - 20, "|  _____|  |  | |   _   |   |_| |    ___|");
	mvprintw((yScreen / 2) - (NBMODE + 7), xScreen / 2 - 20, "| |_____|   |_| |  |_|  |      _|   |___");
	mvprintw((yScreen / 2) - (NBMODE + 6), xScreen / 2 - 20, "|_____  |  _    |       |     |_|    ___|");
	mvprintw((yScreen / 2) - (NBMODE + 5), xScreen / 2 - 20, " _____| | | |   |   _   |    _  |   |___");
	mvprintw((yScreen / 2) - (NBMODE + 4), xScreen / 2 - 20, "|_______|_|  |__|__| |__|___| |_|_______|");
	for (int i = 0; i < NBMODE; ++i)
	{
		if (i == choice)
			attron(COLOR_PAIR(SELECTED));
		else
			attron(COLOR_PAIR(NORMAL));
		mvprintw((yScreen / 2) - (NBMODE - i * 2), xScreen / 2 - mainMenu[i].size() / 2, mainMenu[i].c_str());
	}
	refresh();
}

void NCursesData::DrawNormalMode()
{
	auto i = 0;
	attron(COLOR_PAIR(BACKGROUND));
	while (i < width)
	{
		auto j = 0;
		while (j < height)
		{
			mvprintw(j, i," ");
			j++;
		}
		i++;
	}
	attron(COLOR_PAIR(NORMAL));
	mvprintw(0, width, "player:%s", player.c_str());
	mvprintw(1, width, "score:%d",score);
	refresh();
}

NCursesData::~NCursesData()
{
	shouldLeave = true;
	mutex.unlock();
	display.join();
	input.join();
	curs_set(1);
	endwin();
}
