#include "NCursesData.hpp"
#include "../core/GameObject.hpp"
#include "../core/Snake.hpp"
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

#define CNORMAL 1
#define CSELECTED 2
#define CBACKGROUND 3
#define CSNAKEHEAD 4
#define CSNAKEBODY 5
#define CFOOD 6

NCursesData::NCursesData(int width, int height, std::list<GameObject*> *objects)
{
	initscr();
	curs_set(0);
	noecho();
	start_color();
	getmaxyx(stdscr, yScreen, xScreen);
	init_pair(CNORMAL, COLOR_WHITE, COLOR_BLACK);
	init_pair(CSELECTED, COLOR_BLACK, COLOR_WHITE);
	init_pair(CBACKGROUND, COLOR_BLACK, COLOR_WHITE);
	init_pair(CSNAKEHEAD, COLOR_BLACK, COLOR_RED);
	init_pair(CSNAKEBODY, COLOR_BLACK, COLOR_GREEN);
	init_pair(CFOOD, COLOR_RED, COLOR_WHITE);
	funcs[MAINMENU] = &NCursesData::DrawMainMenu;
	funcs[NM] = &NCursesData::DrawNormalMode;
	funcs[PAUSEMENU] = &NCursesData::DrawPauseMenu;
	funcs2[SNAKE] = &NCursesData::DrawSnake;
	funcs2[FOOD] = &NCursesData::DrawFood;
	this->width = width;
	this->height = height;
	this->objects = objects;
	shouldLeave = false;
	value = NONE;
	inputs['w'] = UP;
	inputs['s'] = DOWN;
	inputs['a'] = LEFT;
	inputs['d'] = RIGHT;
	inputs['p'] = PAUSE;
	inputs[27] = PAUSE;
	inputs[80] = F1;
	inputs[81] = F2;
	inputs[82] = F3;
	inputs['\n'] = VALIDATE;
	// display = std::thread(&NCursesData::StartDisplay, this);
	// input = std::thread(&NCursesData::StartInput, this);
	pauseMenu[0] =  "continue";
	pauseMenu[1] = "restart";
	pauseMenu[2] = "Quit";
}

void NCursesData::Lock()
{
	mutex.lock();
}

void NCursesData::Draw()
{
	getmaxyx(stdscr, yScreen, xScreen);
	clear();
	if (yScreen < height || xScreen < (width + 15))
	{
		attron(COLOR_PAIR(CNORMAL));
		mvprintw(yScreen / 2, xScreen / 2 - 9, "please resize term");
		refresh();
	}
	else
		(this->*funcs[state])();
}

void NCursesData::StartDisplay()
{
	while (!shouldLeave)
	{
		mutex.lock();
		mutex.unlock();
		getmaxyx(stdscr, yScreen, xScreen);
		clear();
		if (yScreen < height || xScreen < (width + 15))
		{
			attron(COLOR_PAIR(CNORMAL));
			mvprintw(yScreen / 2, xScreen / 2 - 9, "please resize term");
			refresh();
		}
		else
			(this->*funcs[state])();
	}
}

void NCursesData::StartInput()
{
	int ch;
	timeout(100);
	while (!shouldLeave && (ch = getch()))
	{
		value = inputs[ch];
	}
}

void NCursesData::CleanInput()
{
	pause.lock();
	value = NONE;
	pause.unlock();
}

eInput NCursesData::GetInput()
{
	int ch;
	timeout(0);
	ch = getch();
	value = inputs[ch];
	return value;
}

void NCursesData::SetChoice(int choice)
{
	this->choice = choice;
}

void NCursesData::SetState(eGameState state)
{
	this->state = state;
}

void NCursesData::DrawMainMenu()
{
	attron(COLOR_PAIR(CNORMAL));
	mvprintw((yScreen / 2) - (NBMODE + 9), xScreen / 2 - 20, " _______ __    _ _______ ___   _ _______");
	mvprintw((yScreen / 2) - (NBMODE + 8), xScreen / 2 - 20, "|  _____|  |  | |   _   |   |_| |    ___|");
	mvprintw((yScreen / 2) - (NBMODE + 7), xScreen / 2 - 20, "| |_____|   |_| |  |_|  |     __|   |___");
	mvprintw((yScreen / 2) - (NBMODE + 6), xScreen / 2 - 20, "|_____  |  _    |       |    |__|    ___|");
	mvprintw((yScreen / 2) - (NBMODE + 5), xScreen / 2 - 20, " _____| | | |   |   _   |    _  |   |___");
	mvprintw((yScreen / 2) - (NBMODE + 4), xScreen / 2 - 20, "|_______|_|  |__|__| |__|___| |_|_______|");
	for (int i = 0; i < NBMODE; ++i)
	{
		if (i == choice)
			attron(COLOR_PAIR(CSELECTED));
		else
			attron(COLOR_PAIR(CNORMAL));
		mvprintw((yScreen / 2) - (NBMODE - i * 2), xScreen / 2 - mainMenu[i].size() / 2, mainMenu[i].c_str());
	}
	refresh();
}

void NCursesData::DrawNormalMode()
{
	auto i = 0;
	attron(COLOR_PAIR(CBACKGROUND));
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
	for (auto i = objects->begin(); i != objects->end(); ++i)
	{
		(this->*funcs2[(*i)->GetType()])(*i);
	}
	attron(COLOR_PAIR(CNORMAL));
	mvprintw(0, width, "player:%s", player.c_str());
	mvprintw(1, width, "score:%d", score);
	refresh();
}

void NCursesData::DrawPauseMenu()
{
	attron(COLOR_PAIR(CNORMAL));
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 9), xScreen / 2 - 20, " _______ _______ __   __ _______ _______ ");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 8), xScreen / 2 - 20, "|    _  |   _   |  | |  |  _____|    ___|");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 7), xScreen / 2 - 20, "|   |_| |  |_|  |  | |  | |_____|   |___ ");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 6), xScreen / 2 - 20, "|    ___|       |  |_|  |_____  |    ___|");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 5), xScreen / 2 - 20, "|   |   |   _   |       |_____| |   |___ ");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 4), xScreen / 2 - 20, "|___|   |__| |__|_______|_______|_______|");
	for (int i = 0; i < NBACTIONPAUSE; i++)
	{
		if (i == choice)
			attron(COLOR_PAIR(CSELECTED));
		else
			attron(COLOR_PAIR(CNORMAL));
		mvprintw((yScreen / 2) - (NBACTIONPAUSE - i * 2), xScreen / 2 - pauseMenu[i].size() / 2, pauseMenu[i].c_str());
	}
	refresh();
}

void NCursesData::DrawSnake(GameObject *it)
{
	auto snake = dynamic_cast<Snake *>(it)->GetSnake();

	for (auto i = snake.begin(); i != snake.end(); ++i)
	{
		if (i == snake.begin())
			attron(COLOR_PAIR(CSNAKEHEAD));
		else
			attron(COLOR_PAIR(CSNAKEBODY));
		mvprintw((*i).getY(), (*i).getX()," ");
	}
}

void NCursesData::DrawFood(GameObject *it)
{
	attron(COLOR_PAIR(CFOOD));
	mvprintw(it->GetPosition().getY(), it->GetPosition().getX(), "o");
}

NCursesData::~NCursesData()
{
	shouldLeave = true;
	// mutex.unlock();
	// display.join();
	// input.join();
	curs_set(1);
	endwin();
}
