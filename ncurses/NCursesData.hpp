#ifndef NCURSESDATA_HPP
#define NCURSESDATA_HPP

#include <Data.hpp>
#include <thread>
#include <map>

enum eActionPause
{
	CONTINUE = 0,
	RESTART,
	EXIT2
};

#define NBACTIONPAUSE 3

class NCursesData : public Data
{
	typedef void (NCursesData::*Func)();
public:
	NCursesData(int width, int height, std::list<GameObject*> *objects);
	void Draw();
	void Lock();
	int GetInput();
	bool ShouldLeave();
	bool ShouldReset();
	void Pause();
	~NCursesData();

private:
	void StartDisplay();
	void StartInput();
	void DrawMainMenu();
	Func funcs[3];
	std::thread display;
	std::thread input;
	int xScreen;
	int yScreen;
	std::map<int, eInput> inputs;
	std::string mainMenu[NBMODE] = {"new game", "quit"};
	std::string pauseMenu[NBACTIONPAUSE] = {"continue", "restart", "exit"};
};

#endif
