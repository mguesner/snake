#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <list>
#include <mutex>

enum gameMode
{
	NM = 0,
	EXIT
};

#define NBMODE 1

class Data
{
public:
	virtual ~Data(){}
	virtual void Draw() = 0;
	virtual void Lock() = 0;
	virtual int GetInput() = 0;
	virtual bool ShouldLeave() = 0;

protected:
	bool shouldLeave;
	gameMode mode;
	int keycode;
	int width;
	int height;
	int value;
	int score;
	std::string player;
	std::list<int> *snake;
	std::list<int> *objects;
	std::mutex mutex;
};

#endif
