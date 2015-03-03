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
public:
	NCursesData(int width, int height, std::list<GameObject&> *objects);
	void Draw();
	void Lock();
	int GetInput();
	bool ShouldLeave();
	void Pause();
	~NCursesData();

private:
	void StartDisplay();
	void StartInput();
	std::thread display;
	std::thread input;
	int xScreen;
	int yScreen;
	bool over;
	std::map<int, eInput> inputs;
};

#endif
