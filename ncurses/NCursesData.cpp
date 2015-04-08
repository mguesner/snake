#include "NCursesData.hpp"
#include "../core/GameObject.hpp"
#include "../core/Snake.hpp"
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
	init_color(COLOR_MARRON, 255, 128, 0);
	init_pair(CNORMAL, COLOR_WHITE, COLOR_BLACK);
	init_pair(CSELECTED, COLOR_BLACK, COLOR_WHITE);
	init_pair(CBACKGROUND, COLOR_BLACK, COLOR_WHITE);
	init_pair(CSNAKEHEAD, COLOR_BLACK, COLOR_RED);
	init_pair(CSNAKEBODY, COLOR_BLACK, COLOR_GREEN);
	init_pair(CFOOD, COLOR_RED, COLOR_WHITE);
	init_pair(CWALL, COLOR_WHITE, COLOR_MARRON);
	funcs[MAINMENU] = &NCursesData::DrawMainMenu;
	funcs[HISCOREMENU] = &NCursesData::DrawHiScoreMenu;
	funcs[NM] = &NCursesData::DrawNormalMode;
	funcs[MULTI] = &NCursesData::DrawMultiMode;
	funcs[MULTIMENU] = &NCursesData::DrawMultiMenu;
	funcs[HOSTMENU] = &NCursesData::DrawHostMenu;
	funcs[JOINMENU] = &NCursesData::DrawJoinMenu;
	funcs[PAUSEMENU] = &NCursesData::DrawPauseMenu;
	funcs[ENDMENU] = &NCursesData::DrawEndMenu;
	funcs[BESTENDMENU] = &NCursesData::DrawBestEndMenu;
	funcs2[SNAKE] = &NCursesData::DrawSnake;
	funcs2[FOOD] = &NCursesData::DrawFood;
	this->width = width;
	this->height = height;
	this->objects = objects;
	keypad(stdscr, TRUE);
	shouldLeave = false;
	closeIsCall = false;
	locker.lock();
	value = NONE;
	inputs['w'] = UP;
	inputs['s'] = DOWN;
	inputs['a'] = LEFT;
	inputs['d'] = RIGHT;
	inputs['p'] = PAUSE;
	inputs[KEY_UP] = UP;
	inputs[KEY_DOWN] = DOWN;
	inputs[KEY_LEFT] = LEFT;
	inputs[KEY_RIGHT] = RIGHT;
	inputs[27] = PAUSE;
	inputs[81] = F2;
	inputs[82] = F3;
	inputs['2'] = F2;
	inputs['3'] = F3;
	inputs['\n'] = VALIDATE;
	// display = std::thread(&NCursesData::StartDisplay, this);
	// input = std::thread(&NCursesData::StartInput, this);
	pauseMenu[0] =  "continue";
	pauseMenu[1] = "restart";
	pauseMenu[2] = "quit";
	mainMenu[NEWGAME] = "new game";
	mainMenu[MULTIPLAYER] = "multiplayer";
	mainMenu[HISCORE] = "hi-score";
	mainMenu[WALL] = "wall-e : ";
	mainMenu[EXIT] = "quit";
	endMenu[0] = "restart";
	endMenu[1] = "main menu";
	endMenu[2] = "quit";
	multiMenu[0] = "host game";
	multiMenu[1] = "join game";
	multiMenu[2] = "quit";
}

void NCursesData::Start()
{
	while (!closeIsCall);
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

eInput NCursesData::GetInput()
{
	int ch;
	timeout(0);
	ch = getch();
	value = inputs[ch];
	return value;
}

void NCursesData::DrawMainMenu()
{
	attron(COLOR_PAIR(CNORMAL));
	mvprintw((yScreen / 2) - (SIZEMENUCHOICES + 9), xScreen / 2 - 20, " _______ __    _ _______ ___   _ _______");
	mvprintw((yScreen / 2) - (SIZEMENUCHOICES + 8), xScreen / 2 - 20, "|  _____|  |  | |   _   |   |_| |    ___|");
	mvprintw((yScreen / 2) - (SIZEMENUCHOICES + 7), xScreen / 2 - 20, "| |_____|   |_| |  |_|  |     __|   |___");
	mvprintw((yScreen / 2) - (SIZEMENUCHOICES + 6), xScreen / 2 - 20, "|_____  |  _    |       |    |__|    ___|");
	mvprintw((yScreen / 2) - (SIZEMENUCHOICES + 5), xScreen / 2 - 20, " _____| | | |   |   _   |    _  |   |___");
	mvprintw((yScreen / 2) - (SIZEMENUCHOICES + 4), xScreen / 2 - 20, "|_______|_|  |__|__| |__|___| |_|_______|");
	for (int i = 0; i < SIZEMENUCHOICES; ++i)
	{
		if (i == choice)
			attron(COLOR_PAIR(CSELECTED));
		else
			attron(COLOR_PAIR(CNORMAL));
		mvprintw((yScreen / 2) - (SIZEMENUCHOICES - i * 2), xScreen / 2 - (mainMenu[i].size() / 2 + (i == WALL ? 1 : 0)), "%s%s", mainMenu[i].c_str(), i == WALL ? (wall ? "ON" : "OFF") : "");
	}
	refresh();
}

void NCursesData::DrawHiScoreMenu()
{
	attron(COLOR_PAIR(CNORMAL));
	mvprintw((yScreen / 2) - (10 + 9), xScreen / 2 - 34, " __   __  ___          _______  _______  _______  ______    _______ ");
	mvprintw((yScreen / 2) - (10 + 8), xScreen / 2 - 34, "|  |_|  ||   |        |  _____||     __||   _   ||    _ |  |    ___|");
	mvprintw((yScreen / 2) - (10 + 7), xScreen / 2 - 34, "|       ||   |  ____  | |_____ |    |   |  | |  ||   |_||_ |   |___ ");
	mvprintw((yScreen / 2) - (10 + 6), xScreen / 2 - 34, "|       ||   | |____| |_____  ||    |   |  | |  ||    __  ||    ___|");
	mvprintw((yScreen / 2) - (10 + 5), xScreen / 2 - 34, "|   _   ||   |         _____| ||    |__ |  |_|  ||   |  | ||   |___ ");
	mvprintw((yScreen / 2) - (10 + 4), xScreen / 2 - 34, "|__| |__||___|        |_______||_______||_______||___|  |_||_______|");
	mvprintw((yScreen / 2) - (10 + 2), xScreen / 2 - 5, "With wall :");
	mvprintw((yScreen / 2) - (10 + 1), xScreen / 2 - 3, "%s : %d", hiScores->GetPseudo(0, true), hiScores->GetScore(0, true));
	mvprintw((yScreen / 2) - 10, xScreen / 2 - 3, "%s : %d", hiScores->GetPseudo(1, true), hiScores->GetScore(1, true));
	mvprintw((yScreen / 2) - (10 - 1), xScreen / 2 - 3, "%s : %d", hiScores->GetPseudo(2, true), hiScores->GetScore(2, true));
	mvprintw((yScreen / 2) - (10 - 2), xScreen / 2 - 3, "%s : %d", hiScores->GetPseudo(3, true), hiScores->GetScore(3, true));
	mvprintw((yScreen / 2) - (10 - 3), xScreen / 2 - 3, "%s : %d", hiScores->GetPseudo(4, true), hiScores->GetScore(4, true));
	mvprintw((yScreen / 2) - (10 - 5), xScreen / 2 - 5, "Without wall :");
	mvprintw((yScreen / 2) - (10 - 6), xScreen / 2 - 3, "%s : %d", hiScores->GetPseudo(0, false), hiScores->GetScore(0, false));
	mvprintw((yScreen / 2) - (10 - 7), xScreen / 2 - 3, "%s : %d", hiScores->GetPseudo(1, false), hiScores->GetScore(1, false));
	mvprintw((yScreen / 2) - (10 - 8), xScreen / 2 - 3, "%s : %d", hiScores->GetPseudo(2, false), hiScores->GetScore(2, false));
	mvprintw((yScreen / 2) - (10 - 9), xScreen / 2 - 3, "%s : %d", hiScores->GetPseudo(3, false), hiScores->GetScore(3, false));
	mvprintw((yScreen / 2) - (10 - 10), xScreen / 2 - 3, "%s : %d", hiScores->GetPseudo(4, false), hiScores->GetScore(4, false));
	refresh();
}

void NCursesData::DrawNormalMode()
{
	auto i = 0;
	attron(COLOR_PAIR(CWALL));
	while (wall && i < height + 2)
	{
		mvprintw(i, 0, " ");
		mvprintw(i, width + 1, " ");
		i++;
	}
	i = 0;
	while (wall && i < width + 1)
	{
		mvprintw(0, i, " ");
		mvprintw(height + 1, i, " ");
		i++;
	}
	i = 0;
	attron(COLOR_PAIR(CBACKGROUND));
	while (i < width)
	{
		auto j = 0;
		while (j < height)
		{
			mvprintw(j + (wall ? 1 : 0), i + (wall ? 1 : 0)," ");
			j++;
		}
		i++;
	}
	for (auto i = objects->begin(); i != objects->end(); ++i)
	{
		(this->*funcs2[(*i)->GetType()])(*i);
	}
	attron(COLOR_PAIR(CNORMAL));
	// mvprintw(0, width + 3, "player: %s", player.c_str());
	mvprintw(1, width + 3, "score: %d", score);
	refresh();
}

void NCursesData::DrawMultiMode()
{
	auto i = 0;
	attron(COLOR_PAIR(CWALL));
	while (wall && i < height + 2)
	{
		mvprintw(i, 0, " ");
		mvprintw(i, width + 1, " ");
		i++;
	}
	i = 0;
	while (wall && i < width + 1)
	{
		mvprintw(0, i, " ");
		mvprintw(height + 1, i, " ");
		i++;
	}
	i = 0;
	attron(COLOR_PAIR(CBACKGROUND));
	while (i < width)
	{
		auto j = 0;
		while (j < height)
		{
			mvprintw(j + (wall ? 1 : 0), i + (wall ? 1 : 0)," ");
			j++;
		}
		i++;
	}
	for (auto i = objects->begin(); i != objects->end(); ++i)
	{
		(this->*funcs2[(*i)->GetType()])(*i);
	}
	attron(COLOR_PAIR(CNORMAL));
	// mvprintw(0, width + 3, "player:%s", player.c_str());
	mvprintw(1, width + 3, "score:%d", score);
	refresh();
}

void NCursesData::DrawHostMenu()
{
	mvprintw(yScreen / 2, xScreen / 2, "waiting players");
}

void NCursesData::DrawJoinMenu()
{
	char tmp[16];
	mvprintw(yScreen / 2, xScreen / 2, "enter ip : ");
	echo();
	curs_set(1);
	timeout(-1);
	getnstr(tmp, 15);
	ip = std::string(tmp);
	timeout(0);
	noecho();
	curs_set(0);
}

void NCursesData::DrawMulti()
{
	//mvprintw()
}


void NCursesData::DrawMultiMenu()
{
	for (int i = 0; i < NBACTIONMULTIMENU; i++)
	{
		if (i == choice)
			attron(COLOR_PAIR(CSELECTED));
		else
			attron(COLOR_PAIR(CNORMAL));
		mvprintw((yScreen / 2) - (NBACTIONMULTIMENU - i * 2), xScreen / 2 - multiMenu[i].size() / 2, multiMenu[i].c_str());
	}
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

void NCursesData::DrawEndMenu()
{
	attron(COLOR_PAIR(CNORMAL));
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 9), xScreen / 2 - 38, " _______  _______  __   __  _______    _______  __   __  _______  ______   ");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 8), xScreen / 2 - 38, "|    ___||   _   ||  |_|  ||    ___|  |   _   ||  |_|  ||    ___||    _ |  ");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 7), xScreen / 2 - 38, "|   | __ |  |_|  ||       ||   |___   |  | |  ||       ||   |___ |   |_||_ ");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 6), xScreen / 2 - 38, "|   ||  ||       ||       ||    ___|  |  | |  ||       ||    ___||    __  |");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 5), xScreen / 2 - 38, "|   |_| ||   _   || ||_|| ||   |___   |  |_|  | |     | |   |___ |   |  | |");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 4), xScreen / 2 - 38, "|_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_|");
	mvprintw((yScreen / 2) - 4, xScreen / 2 - 8, "your score : %d", score);
	for (int i = 0; i < NBACTIONPAUSE; i++)
	{
		if (i == choice)
			attron(COLOR_PAIR(CSELECTED));
		else
			attron(COLOR_PAIR(CNORMAL));
		mvprintw((yScreen / 2) - (NBACTIONPAUSE - i * 2) + 2, xScreen / 2 - endMenu[i].size() / 2, endMenu[i].c_str());
	}
	refresh();
}

void NCursesData::DrawBestEndMenu()
{
	attron(COLOR_PAIR(CNORMAL));
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 9), xScreen / 2 - 38, " _______  _______  __   __  _______    _______  __   __  _______  ______   ");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 8), xScreen / 2 - 38, "|    ___||   _   ||  |_|  ||    ___|  |   _   ||  |_|  ||    ___||    _ |  ");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 7), xScreen / 2 - 38, "|   | __ |  |_|  ||       ||   |___   |  | |  ||       ||   |___ |   |_||_ ");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 6), xScreen / 2 - 38, "|   ||  ||       ||       ||    ___|  |  | |  ||       ||    ___||    __  |");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 5), xScreen / 2 - 38, "|   |_| ||   _   || ||_|| ||   |___   |  |_|  | |     | |   |___ |   |  | |");
	mvprintw((yScreen / 2) - (NBACTIONPAUSE + 4), xScreen / 2 - 38, "|_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_|");
	mvprintw((yScreen / 2) - 4, xScreen / 2 - 8, "your score : %d", score);
	for (int i = 0; i < 3; i++)
	{
		if (i == choice)
			attron(COLOR_PAIR(CSELECTED));
		else
			attron(COLOR_PAIR(CNORMAL));
		mvprintw((yScreen / 2), xScreen / 2 - 1 + i, "%c", player[i]);
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
		mvprintw((*i).getY() + (wall ? 1 : 0), (*i).getX() + (wall ? 1 : 0)," ");
	}
}

void NCursesData::DrawFood(GameObject *it)
{
	attron(COLOR_PAIR(CFOOD));
	mvprintw(it->GetPosition().getY() + (wall ? 1 : 0), it->GetPosition().getX() + (wall ? 1 : 0), "o");
}

NCursesData::~NCursesData()
{
	shouldLeave = true;
	curs_set(1);
	endwin();
}
