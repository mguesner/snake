#ifndef NCURSESDATA_HPP
#define NCURSESDATA_HPP

#include <Data.hpp>
#include <thread>

#define CNORMAL 1
#define CSELECTED 2
#define CBACKGROUND 3
#define CSNAKEHEAD 4
#define CSNAKEBODY 5
#define CFOOD 6
#define CWALL 7

#define COLOR_MARRON 20

class NCursesData : public Data
{
	typedef void (NCursesData::*Func)();
	typedef void (NCursesData::*Func2)(GameObject*);
public:
	NCursesData(int width, int height, std::list<GameObject*> *objects);
	void Draw();
	void Close();
	void Start();
	eInput GetInput();
	~NCursesData();

private:
	bool shouldLeave;
	void StartDisplay();
	void StartInput();
	void DrawMainMenu();
	void DrawPseudoMenu();
	void DrawNormalMode();
	void DrawPauseMenu();
	void DrawEndMenu();
	void DrawSnake(GameObject*);
	void DrawFood(GameObject*);
	Func funcs[6];
	Func2 funcs2[2];
	int xScreen;
	int yScreen;
};

#endif
