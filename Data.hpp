#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <list>
#include <mutex>

class GameObject;

enum ObjectType
{
	SNAKE = 0,
	FOOD = 1,
	VOID =2
};

enum eGameState
{
	MAINMENU = 0,
	NM,
	MULTI,
	PAUSEMENU
};

enum eInput
{
	NONE = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	PAUSE,
	F1,
	F2,
	F3,
	VALIDATE
};

#define NBMODE 2



class Data
{
public:
	virtual ~Data(){}
	virtual void Draw() = 0;
	virtual void Lock() = 0;
	virtual void CleanInput() = 0;
	virtual eInput GetInput() = 0;
	std::mutex pause;
	virtual void SetChoice(int) = 0;
	virtual void SetState(eGameState) = 0;

protected:
	eGameState state;
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
