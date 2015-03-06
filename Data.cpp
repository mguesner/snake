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
