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
	void Lock();
	virtual void CleanInput();
	virtual eInput GetInput();
	~NCursesData();

private:
	bool shouldLeave;
	void StartDisplay();
	void StartInput();
	void DrawMainMenu();
	void DrawNormalMode();
	void DrawPauseMenu();
	void DrawSnake(GameObject*);
	void DrawFood(GameObject*);
	Func funcs[4];
	Func2 funcs2[2];
	std::thread display;
	std::thread input;
	int xScreen;
	int yScreen;
	std::map<int, eInput> inputs;
	std::string mainMenu[NBMODE] = {"new game", "quit"};
	std::string pauseMenu[NBACTIONPAUSE];
};

#endif
