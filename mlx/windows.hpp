#ifndef WINDOWS_HPP
# define WINDOWS_HPP


extern"C"
{
	#include <mlx.h>
	#include "lib/easylibx.h"
}

#include <iostream>
#include <exception>
#include <functional>
#include <cstring>
#include <thread>
#include <mutex>
#include <list>

class MLXData;

#define WIDTH 1900
#define HEIGHT 1080
class Windows
{
public:
	Windows();
	Windows(std::string name, unsigned int width, unsigned int height);
	Windows(std::string name);
	Windows(MLXData *);


	void	pixelToImg(int x, int y, int color);
	void	clearImg();
	void	Run();

	void	*getMlx();
	void	*getImgWin();
	void	*getWin();
	int		getWidth();
	int		getHeight();
	void	Destroy();

	void DrawMainMenu();
	void DrawPseudoMenu();
	void DrawNormalMode();
	void DrawPauseMenu();


	void DrawSquare(int x, int y, int color);


	MLXData *Pipe;
	std::mutex mtx;
	std::mutex isLaunch;
	bool	IsAlive;
	~Windows();

private:
	Windows(const Windows& src);
	void		*mlx;
	void		*win;
	void		*img_mlx;
	void		*img_win;
	void		*terrain;
	int			ptr;
	int			size;
	int			dude;
	char		*data;
	int			width;
	int			height;
};

int key_hook(int keycode);
int expose_hook();
int redraw();
int expose_hook(Windows *a);

#endif
