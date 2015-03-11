#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <list>
#include <mutex>
#include <map>

class GameObject;

enum ObjectType
{
	SNAKE = 0,
	FOOD = 1,
	VOID = 2
};

enum eGameState
{
	MAINMENU = 0,
	PSEUDOMENU,
	NM,
	MULTIMENU,
	HOSTMENU,
	JOINMENU,
	MULTI,
	PAUSEMENU,
	ENDMENU
};

enum eMenuChoice
{
	NEWGAME = 0,
	MULTIPLAYER,
	WALL,
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
#define NBACTIONEND 3
#define NBMODE 4


class Data
{
public:
	Data();
	virtual ~Data(){}
	virtual void Start() = 0;
	virtual void Draw() = 0;
	virtual eInput GetInput() = 0;
	void Unlocker();
	void Close();
	void SetDrawFinish();
	bool GetDrawInstruction();
	bool ShouldClose();
	void CleanInput();
	int GetChoice();
	void SetScore(int);
	void SetWall(bool);
	int GetScore();
	std::list<GameObject*> *GetGameObjects();
	eGameState GetState();
	virtual void SetChoice(int);
	virtual void SetState(eGameState);

protected:
	eGameState state;
	int keycode;
	int width;
	int height;
	int choice;
	bool wall;
	eInput value;
	std::list<GameObject*> *objects;
	int score;
	std::string player;
	std::map<int, eInput> inputs;
	std::string mainMenu[NBMODE];
	std::string pauseMenu[NBACTIONPAUSE];
	std::string endMenu[NBACTIONEND];
	bool shouldDraw;
	bool closeIsCall;
	std::mutex locker;

};

#endif
