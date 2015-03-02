#include "NCursesData.hpp"
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

NCursesData::NCursesData(int width, int height, std::list<int> *snake
	, std::list<int> *objects)
{
	initscr();
	curs_set(0);
	noecho();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_RED, COLOR_WHITE);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	this->width = width;
	this->height = height;
	this->snake = snake;
	this->objects = objects;
	over = false;
	value = 0;
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
			attron(COLOR_PAIR(5));
			mvprintw(yScreen / 2, xScreen / 2 - 9, "please resize term");
			refresh();
			continue;
		}
		clear();
		auto i = 0;
		attron(COLOR_PAIR(2));
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
		auto current = snake->begin();
		auto end = snake->end();
		while(current != end)
		{
			auto prout = *current;
			auto x = prout % 50;
			auto y = prout / 50;
			if (prout == snake->front())
				attron(COLOR_PAIR(1));
			else
				attron(COLOR_PAIR(3));
			mvprintw(y % height, x % width," ");
			current++;
		}
		auto current2 = objects->begin();
		auto end2 = objects->end();
		while(current2 != end2)
		{
			auto prout2 = *current2;
			auto x = prout2 % 50;
			auto y = prout2 / 50;
			attron(COLOR_PAIR(4));
			mvprintw(y % height, x % width,"#");
			current2++;
		}
		attron(COLOR_PAIR(5));
		mvprintw(0, width, "score:%d", score);
		refresh();
	}
}

void NCursesData::StartInput()
{
	while ((value = getch()))
	{
		if (value == 27)
			break;
	}
}

int NCursesData::GetInput()
{
	return value;
}

NCursesData::~NCursesData()
{
	mutex.unlock();
	curs_set(1);
	over = true;
	display.join();
	input.join();
	endwin();
}
