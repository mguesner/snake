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
	this->width = width;
	this->height = height;
	this->snake = snake;
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
		//clear();
		auto i = 0;
		while (i )
		auto current = snake->begin();
		auto end = snake->end();
		while(current != end)
		{
			auto prout = *current;
			auto x = prout % 50;
			auto y = prout / 50;
			if (prout == snake->front())
				mvprintw(y % height, x % width,"0");
			else if (prout == snake->back())
				mvprintw(y % height, x % width,"-");
			else
				mvprintw(y % height, x % width,"~");
			current++;
		}
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
