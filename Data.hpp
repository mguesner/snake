#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <list>

class Data
{
public:
	virtual ~Data(){}
	virtual void Draw() = 0;
	virtual void Lock() = 0;
	virtual int GetInput() = 0;

protected:
	int width;
	int height;
	int value;
	std::list<int> *snake;
	std::list<int> *objects;
	std::mutex mutex;
};

#endif
