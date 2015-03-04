#include "NCursesData.hpp"
#include "Menu.hpp"
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

NCursesData::NCursesData(int width, int height, std::list<GameObject&> *objects)
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
	this->width = width;
	this->height = height;
	this->objects = objects;
	over = false;
	value = NONE;
	Menu menu(xScreen, yScreen);
	mode = menu.Display();
	if(!(shouldLeave = (mode == NBMODE - 1)))
		player = menu.Name();
	inputs['w'] = UP;
	inputs['s'] = DOWN;
	inputs['a'] = LEFT;
	inputs['d'] = RIGHT;
	inputs['p'] = PAUSE;
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
	srand(time(NULL));
	while (!over)
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
		auto current = objects->begin();
		auto end = objects->end();
		while(current != end)
		{
		// 	auto prout = *current;
		// 	auto x = current-> 50;
		// 	auto y = prout / 50;
		// 	if (prout == snake->front())
		// 		attron(COLOR_PAIR(SNAKEHEAD));
		// 	else
		// 		attron(COLOR_PAIR(SNAKEBODY));
		// 	mvprintw(y % height, x % width," ");
		// 	current++;
		// }
		// auto current2 = objects->begin();
		// auto end2 = objects->end();
		// while(current2 != end2)
		// {
		// 	auto prout2 = *current2;
		// 	auto x = prout2 % 50;
		// 	auto y = prout2 / 50;
		// 	attron(COLOR_PAIR(FOOD));
		// 	mvprintw(y % height, x % width,"#");
		// 	current2++;
		}
		attron(COLOR_PAIR(NORMAL));
		mvprintw(0, width, "player:%s", player.c_str());
		mvprintw(1, width, "score:%d",score);
		refresh();
	}
}

void NCursesData::StartInput()
{
	int ch;
	timeout(200);
	while (!shouldLeave && (ch = getch()))
	{
		value = inputs[ch];
		//mvprintw(0,0,"%d", value);
		pause.lock();
		pause.unlock();
	}
}

int NCursesData::GetInput()
{
	return value;
}

bool NCursesData::ShouldLeave()
{
	return shouldLeave;
}

void NCursesData::Pause()
{
	pause.lock();
	Menu menu(xScreen, yScreen);
	auto res = menu.Pause();
	if (res == EXIT2)
		shouldLeave = true;
	pause.unlock();
}

NCursesData::~NCursesData()
{
	shouldLeave = true;
	mutex.unlock();
	over = true;
	display.join();
	input.join();
	curs_set(1);
	endwin();
}
