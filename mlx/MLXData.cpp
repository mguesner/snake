#include "MLXData.hpp"


MLXData::MLXData(int width, int height, std::list<GameObject*> *objects)
{
	this->width = width;
	this->height = height;
	this->objects = objects;
	win = new Windows();
	value = NONE;
}

void MLXData::Draw()
{

}

void MLXData::Lock()
{

}

eInput MLXData::GetInput()
{
	return value;
}

void MLXData::CleanInput()
{
}

void MLXData::SetChoice(int set)
{
	choice = set;
}

void MLXData::SetState(eGameState set)
{
	state = set;
}

MLXData::~MLXData()
{
}
