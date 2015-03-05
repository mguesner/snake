#include "MLXData.hpp"

MLXData::MLXData(int width, int height, std::list<GameObject*> *objects)
{
	if ((mlx = mlx_init()) == NULL)
		throw std::exception();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, (char*)"snake");
	img_win = mlx_new_image(mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(img_win, &ptr, &size, &raf);
	ft_handle_loop(win, mlx, this, 0);
	mlx_loop(mlx);
	this->width = width;
	this->height = height;
	this->objects = objects;
	value = NONE;
}
void MLXData::Draw()
{

}

void MLXData::Lock()
{

}

eInput MLXData::GetInput()
{
	return value;
}

void MLXData::SetChoice(int set)
{
	choice = set;
}

void MLXData::SetState(eGameState set)
{
	state = set;
}

MLXData::~MLXData()
{
}

