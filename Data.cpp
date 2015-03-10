#include "Data.hpp"

Data::Data()
{
	score = 1;
}

void Data::SetScore(int value)
{
	score = value;
}

int Data::GetScore()
{
	return score;
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

void Data::Unlocker()
{
	locker.unlock();
}

void Data::Close()
{
	closeIsCall = true;
}


bool Data::ShouldClose()
{
	return closeIsCall;
}