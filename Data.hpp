#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <list>
#include <mutex>

enum eGameMode
{
	NM = 0,
	EXIT
};

enum eInput
{
	NONE = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	PAUSE
};

#define NBMODE 2

class Data
{
public:
	virtual ~Data(){}
	virtual void Draw() = 0;
	virtual void Lock() = 0;
	virtual int GetInput() = 0;
	virtual bool ShouldLeave() = 0;
	virtual void Pause() = 0;

protected:
	bool shouldLeave;
	eGameMode mode;
	int keycode;
	int width;
	int height;
	eInput value;
	int score;
	std::string player;
	std::list<int> *snake;
	std::list<int> *objects;
	std::mutex mutex;
};

#endif
