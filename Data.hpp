#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <list>
#include "core/GameObject.hpp"

enum ObjectType
{
	SNAKE = 0,
	FOOD
};

class Data
{
public:
	virtual ~Data(){}
	virtual void Draw() = 0;
	virtual void Lock() = 0;
	virtual int GetInput() = 0;
	std::mutex pause;
protected:
	int keycode;
	int width;
	int height;
	int value;
	std::list<GameObject&> *objects;
	std::mutex mutex;
};

#endif
