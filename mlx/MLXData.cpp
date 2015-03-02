#include "MLXData.hpp"

MLXData::MLXData(int width, int height, std::list<int> *snake
	, std::list<int> *objects)
{
	if ((mlx = mlx_init()) == NULL)
		throw std::exception();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, (char*)"default mod1 window");
	img_win = mlx_new_image(mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(img_win, &ptr, &size, &raf);
	ft_handle_loop(win, mlx, this, 0);
	this->width = width;
	this->height = height;
	this->snake = snake;
	this->objects = objects;
	value = 0;
}
void MLXData::Draw()
{

}

void MLXData::Lock()
{

}

int MLXData::GetInput()
{
	return value;
}

MLXData::~MLXData()
{
}

