#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <list>

class Data
{
public:
	virtual ~Data(){}
	virtual void Draw() = 0;

protected:
	int width;
	int height;
	std::list<int, int> *snake;
	std::list<int , int> *objects;
	std::mutex mutex;


};

#endif
