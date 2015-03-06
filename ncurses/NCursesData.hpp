#ifndef NCURSESDATA_HPP
#define NCURSESDATA_HPP

#include <Data.hpp>
#include <thread>
#include <map>

class NCursesData : public Data
{
	typedef void (NCursesData::*Func)();
	typedef void (NCursesData::*Func2)(GameObject*);
public:
	NCursesData(int width, int height, std::list<GameObject*> *objects);
	void Draw();
	eInput GetInput();
	~NCursesData();

private:
	bool shouldLeave;
	void StartDisplay();
	void StartInput();
	void DrawMainMenu();
	void DrawNormalMode();
	void DrawPauseMenu();
	void DrawEndMenu();
	void DrawSnake(GameObject*);
	void DrawFood(GameObject*);
	Func funcs[5];
	Func2 funcs2[2];
	int xScreen;
	int yScreen;
	std::map<int, eInput> inputs;
	std::string mainMenu[NBMODE];
	std::string pauseMenu[NBACTIONPAUSE];
};

#endif
