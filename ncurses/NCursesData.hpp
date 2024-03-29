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
#define CPOWERUP 8

#define COLOR_MARRON 20

class NCursesData : public Data
{
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
	void DrawHiScoreMenu();
	void DrawNormalMode();
	void DrawMultiMode();
	void DrawMulti();
	void DrawMultiMenu();
	void DrawHostMenu();
	void DrawJoinMenu();
	void DrawPauseMenu();
	void DrawEndMenu();
	void DrawBestEndMenu();
	void DrawSnake(GameObject*);
	void DrawFood(GameObject*);
	void DrawPowerUp(GameObject*);
	void DrawObstacle(GameObject*);
	int xScreen;
	int yScreen;
};

#endif
