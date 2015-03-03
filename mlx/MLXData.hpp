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
	MLXData(int width, int height, std::list<int> *snake
	, std::list<int> *objects);
	void Draw();
	void Lock();
	int GetInput();
	~MLXData();

private:
	void		*mlx;
	void		*win;
	void		*img_mlx;
	void		*img_win;
	int			ptr;
	int			size;
	int			raf;
	char		*data;
	int			width;
	int			height;
};

#endif
