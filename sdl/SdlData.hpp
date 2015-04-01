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
	void Start();
	eInput GetInput();
	void SetInput(int);
	~SdlData();

private:

	void		DrawMainMenu();
	void		DrawPseudoMenu();
	void		DrawNormalMode();
	void		DrawMulti();
	void		DrawMultiMenu();
	void		DrawHostMenu();
	void		DrawJoinMenu();
	void		DrawPauseMenu();
	void		DrawEndMenu();
	void		DrawSnake(GameObject*);
	void		DrawFood(GameObject*);
	int			width;
	int			height;
	int			x0;
	int			y0;
	Func		funcs[9];
	Func2		funcs2[2];
	SDL_Window	*win;
	SDL_Surface	*screenSurface;
};

#endif
