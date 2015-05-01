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

enum eMenuMultiChoice
{
	HOST = 0,
	JOIN,
	MMEXIT,
	SIZEMULTIMENUCHOICES
};

enum eInput
{
	NONE = 0,
	CHAR,
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
	typedef void (Data::*Func)();
	typedef void (Data::*Func2)(GameObject*);
public:
	Data();
	Data(int, int, std::list<GameObject*>*);
	virtual ~Data(){}
	virtual void Draw() = 0;
	virtual eInput GetInput() = 0;
	char GetChar();
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
	void SetIp(std::string);
	std::list<GameObject*> *GetGameObjects();
	eGameState GetState();
	void SetIpInfo(std::string info);
	virtual void SetChoice(int);
	virtual void SetState(eGameState);

protected:
	virtual void DrawMainMenu() = 0;
	virtual void DrawHiScoreMenu() = 0;
	virtual void DrawNormalMode() = 0;
	virtual void DrawMultiMode() = 0;
	virtual void DrawMulti() = 0;
	virtual void DrawMultiMenu() = 0;
	virtual void DrawHostMenu() = 0;
	virtual void DrawJoinMenu() = 0;
	virtual void DrawPauseMenu() = 0;
	virtual void DrawEndMenu() = 0;
	virtual void DrawBestEndMenu() = 0;

	virtual void DrawSnake(GameObject*) = 0;
	virtual void DrawFood(GameObject*) = 0;

	Func2 funcs2[2];
	Func funcs[SIZEGSTATE];

	eGameState state;
	int keycode;
	int width;
	int height;
	int choice;
	char ch;
	bool wall;
	bool isMulti;
	eInput value;
	Score *hiScores;
	std::list<GameObject*> *objects;
	int score;
	char player[3];
	std::string ip;
	std::string myAccess;
	std::map<int, eInput> inputs;
	std::map<int, char> chars;
	std::string mainMenu[SIZEMENUCHOICES];
	std::string pauseMenu[NBACTIONPAUSE];
	std::string endMenu[NBACTIONEND];
	std::string multiMenu[NBACTIONMULTIMENU];
	std::string hiScoreMenu[NBACTIONMULTIMENU];
	bool shouldDraw;
	bool closeIsCall;

};

#endif
