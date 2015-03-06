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

enum eActionPause
{
	CONTINUE = 0,
	RESTART,
	EXIT2
};

#define NBACTIONPAUSE 3
#define NBMODE 3


class Data
{
public:
	Data();
	virtual ~Data(){}
	virtual void Draw() = 0;
	virtual void Lock() = 0;
	virtual void CleanInput() = 0;
	virtual eInput GetInput() = 0;
	void SetScore(int);
	int GetScore();
	std::mutex pause;
	virtual void SetChoice(int);
	virtual void SetState(eGameState);

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
