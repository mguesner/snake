#ifndef MLXDATA_HPP
#define MLXDATA_HPP

#include <Data.hpp>
extern"C"
{
	#include <mlx.h>
	#include "lib/easylibx.h"
}

#define WIDTH 1900
#define HEIGHT 1080

class MLXData : public Data
{
public:
	MLXData(int width, int height, std::list<GameObject*> *objects);
	void Draw();
	void Lock();
	eInput GetInput();
	void SetChoice(int);
	void SetState(eGameState);
	void CleanInput();
	char		*data;
	void		*win;
	void		*mlx;
	void		*img_win;
	~MLXData();

private:
	void		*img_mlx;
	int			ptr;
	int			size;
	int			raf;
	int			width;
	int			height;
};

#endif
