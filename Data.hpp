#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <list>
#include <mutex>

class GameObject;

enum ObjectType
{
	SNAKE = 0,
	FOOD
};


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
	PAUSE,
	VALIDATE
};

#define NBMODE 2



class Data
{
public:
	virtual ~Data(){}
	virtual void Draw() = 0;
	virtual void Lock() = 0;
	virtual int GetInput() = 0;
	std::mutex pause;
	virtual bool ShouldLeave() = 0;
	virtual bool ShouldReset() = 0;
	virtual void Pause() = 0;

protected:
	bool shouldLeave;
	bool shouldReset;
	eGameMode mode;
	int keycode;
	int width;
	int height;
	int choice;
	eInput value;
	std::list<GameObject*> *objects;
	int score;
	std::string player;
	std::mutex mutex;
};

#endif
