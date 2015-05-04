#ifndef MLXDATA_HPP
#define MLXDATA_HPP

#include <Data.hpp>
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH		1920
#define HEIGHT		1080

class SdlData : public Data
{
	typedef void (SdlData::*Func)();
	typedef void (SdlData::*Func2)(GameObject*);
public:
	SdlData(int width, int height, std::list<GameObject*> *objects);
	void Draw();
	void Close();
	void Lock();
	eInput GetInput();
	void SetInput(int);
	~SdlData();

private:

	void		DrawMainMenu();
	void		DrawHiScoreMenu();
	void		DrawNormalMode();
	void		DrawMultiMode();
	void		DrawMulti();
	void		DrawMultiMenu();
	void		DrawHostMenu();
	void		DrawJoinMenu();
	void		DrawPauseMenu();
	void		DrawEndMenu();
	void		DrawBestEndMenu();

	void		DrawSnake(GameObject*);
	void		DrawFood(GameObject*);
	void		DrawPowerUp(GameObject*);

	int			x0;
	int			y0;
	TTF_Font	*font20;
	TTF_Font	*font70;
	SDL_Window	*win;
	SDL_Surface	*screenSurface;
};

#endif
