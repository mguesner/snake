#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <list>
#include <mutex>
#include <map>
#include "core/Score.hpp"

class GameObject;

enum ObjectType
{
	SNAKE = 0,
	FOOD,
	VOID,
	SIZETOBJ
};

enum eGameState
{
	MAINMENU = 0,
	HISCOREMENU,
	NM,
	MULTIMENU,
	HOSTMENU,
	JOINMENU,
	MULTI,
	PAUSEMENU,
	ENDMENU,
	BESTENDMENU,
	SIZEGSTATE
};

enum eMenuChoice
{
	NEWGAME = 0,
	MULTIPLAYER,
	HISCORE,
	WALL,
	EXIT,
	SIZEMENUCHOICES
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
	VALIDATE,
	SIZEINPUT
};

enum eActionPause
{
	CONTINUE = 0,
	RESTART,
	EXIT2
};

#define NBACTIONPAUSE 3
#define NBACTIONEND 3
#define NBACTIONMULTIMENU 3
#define NBMODE 4


class Data
{
public:
	Data();
	virtual ~Data(){}
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
	void SetPlayer(char[3]);
	void SetScore(Score*);
	int GetScore();
	std::string GetIp();
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
	Score *hiScores;
	std::list<GameObject*> *objects;
	int score;
	char player[3];
	std::string ip;
	std::map<int, eInput> inputs;
	std::string mainMenu[SIZEMENUCHOICES];
	std::string pauseMenu[NBACTIONPAUSE];
	std::string endMenu[NBACTIONEND];
	std::string multiMenu[NBACTIONMULTIMENU];
	std::string hiScoreMenu[NBACTIONMULTIMENU];
	bool shouldDraw;
	bool closeIsCall;
	std::mutex locker;

};

#endif
