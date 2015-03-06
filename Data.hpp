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
	PAUSEMENU,
	ENDMENU
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
	virtual eInput GetInput() = 0;
	void SetScore(int);
	int GetScore();
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
};

#endif
