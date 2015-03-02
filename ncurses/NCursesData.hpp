#ifndef NCURSESDATA_HPP
#define NCURSESDATA_HPP

#include <Data.hpp>
#include <thread>

class NCursesData : public Data
{
public:
	NCursesData(int width, int height, std::list<int> *snake
	, std::list<int> *objects);
	void Draw();
	void Lock();
	int GetInput();
	~NCursesData();

private:
	void StartDisplay();
	void StartInput();
	std::thread display;
	std::thread input;
	bool over;
};

#endif
