#include "MLXData.hpp"

MLXData::MLXData(int width, int height, std::list<GameObject*> *objects)
{
	if ((mlx = mlx_init()) == NULL)
		throw std::exception();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, (char*)"snake");
	img_win = mlx_new_image(mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(img_win, &ptr, &size, &raf);
	ft_handle_loop(win, mlx, this, 0);
	int color = 0x0000FF;
	int x = 0;
	while (x < HEIGHT * WIDTH * 4)
	{
		std::memcpy(&data[x], &color, sizeof(int));
		x += 4;
	}
	mlx_put_image_to_window(mlx, win, img_win, 0, 0);
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

void MLXData::CleanInput()
{
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

