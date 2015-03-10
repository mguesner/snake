#include "MLXData.hpp"


MLXData::MLXData(int width, int height, std::list<GameObject*> *objects)
{
	this->width = width;
	this->height = height;
	this->objects = objects;
	win = new Windows(this);
	value = NONE;
	inputs[13] = UP;
	inputs[1] = DOWN;
	inputs[0] = LEFT;
	inputs[2] = RIGHT;
	inputs[35] = PAUSE;
	inputs[54] = UP;
	inputs[125] = DOWN;
	inputs[54] = LEFT;
	inputs[54] = RIGHT;
	inputs[53] = PAUSE;
	inputs[18] = F1;
	inputs[20] = F3;
	inputs[36] = VALIDATE;
	shouldDraw = false;
	closeIsCall = false;
	locker.lock();
}

void MLXData::Start()
{
	win->Run();
}

void MLXData::Draw()
{
	shouldDraw = true;
}

void MLXData::Lock()
{

}

void MLXData::SetInput(int keycode)
{
	std::cout << keycode << std::endl;
	value = inputs[keycode];
}

eInput MLXData::GetInput()
{
	return value;
}

MLXData::~MLXData()
{
	delete win;
}
