#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <list>
#include <mutex>
#include "core/GameObject.hpp"

#define NBMODE 1

enum ObjectType
{
	SNAKE = 0,
	FOOD
};


enum gameMode
{
	NM = 0,
	EXIT
};




class Data
{
public:
	virtual ~Data(){}
	virtual void Draw() = 0;
	virtual void Lock() = 0;
	virtual int GetInput() = 0;
	std::mutex pause;
	virtual bool ShouldLeave() = 0;

protected:
	bool shouldLeave;
	gameMode mode;
	int keycode;
	int width;
	int height;
	int value;
	std::list<GameObject&> *objects;
	int score;
	std::string player;
	std::mutex mutex;
};

#endif
