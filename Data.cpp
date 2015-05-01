#include "Data.hpp"

Data::Data()
{

}

Data::Data(int width, int height, std::list<GameObject*> *objects)
{
	this->width = width;
	this->height = height;
	this->objects = objects;
	value = NONE;
	closeIsCall = false;
	isMulti = false;

	funcs2[SNAKE] = &Data::DrawSnake;
	funcs2[FOOD] = &Data::DrawFood;

	funcs[MAINMENU] = &Data::DrawMainMenu;
	funcs[HISCOREMENU] = &Data::DrawHiScoreMenu;
	funcs[NM] = &Data::DrawNormalMode;
	funcs[MULTI] = &Data::DrawMultiMode;
	funcs[MULTIMENU] = &Data::DrawMultiMenu;
	funcs[HOSTMENU] = &Data::DrawHostMenu;
	funcs[JOINMENU] = &Data::DrawJoinMenu;
	funcs[PAUSEMENU] = &Data::DrawPauseMenu;
	funcs[ENDMENU] = &Data::DrawEndMenu;
	funcs[BESTENDMENU] = &Data::DrawBestEndMenu;

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
	ip = "127.0.0.1";
}

void Data::SetScore(int value)
{
	score = value;
}

int Data::GetScore()
{
	return score;
}

std::string Data::GetIp()
{
	return ip;
}

void Data::SetChoice(int choice)
{
	this->choice = choice;
}

void Data::SetState(eGameState state)
{
	this->state = state;
}

void Data::SetWall(bool value)
{
	wall = value;
}

eGameState Data::GetState()
{
	return state;
}

bool Data::GetDrawInstruction()
{
	return shouldDraw;
}

void Data::SetDrawFinish()
{
	shouldDraw = false;
}

std::list<GameObject*> *Data::GetGameObjects()
{
	return objects;
}

int Data::GetChoice()
{
	return choice;
}

void Data::CleanInput()
{
	value = NONE;
}

void Data::Close()
{
	closeIsCall = true;
}

void Data::SetPlayer(char player[3])
{
	this->player[0] = player[0];
	this->player[1] = player[1];
	this->player[2] = player[2];
}

char Data::GetChar()
{
	return ch;
}

void Data::SetIpInfo(std::string info)
{
	myAccess = info;
}

void Data::SetScore(Score *score)
{
	hiScores = score;
}

void Data::SetIp(std::string ip)
{
	this->ip = ip;
}

bool Data::ShouldClose()
{
	return closeIsCall;
}
