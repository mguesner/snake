#include "MLXData.hpp"


MLXData::MLXData(int width, int height, std::list<GameObject*> *objects)
{
	this->width = width;
	this->height = height;
	this->objects = objects;
	win = new Windows(this);
	value = NONE;
	inputs['w'] = UP;
	inputs['s'] = DOWN;
	inputs['a'] = LEFT;
	inputs['d'] = RIGHT;
	inputs['p'] = PAUSE;
	inputs[54] = UP;
	inputs[54] = DOWN;
	inputs[54] = LEFT;
	inputs[54] = RIGHT;
	inputs[27] = PAUSE;
	inputs[80] = F1;
	inputs[81] = F2;
	inputs[82] = F3;
	inputs['\n'] = VALIDATE;
}

void MLXData::Start()
{
	win->Run();
}

void MLXData::Draw()
{

}

void MLXData::Lock()
{

}

void MLXData::SetInput(int keycode)
{
	value = inputs[keycode];
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
	delete win;
}
