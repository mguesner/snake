#include "MLXData.hpp"


MLXData::MLXData(int width, int height, std::list<GameObject*> *objects)
{
	if ((mlx = mlx_init()) == NULL)
		throw std::exception();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, (char*)"snake");
	img_win = mlx_new_image(mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(img_win, &ptr, &size, &raf);
	ft_handle_loop(win, mlx, this, 0);
	prout = std::thread(&MLXData::caca, this);
	// mlx_loop(mlx);
	this->width = width;
	this->height = height;
	this->objects = objects;
	value = NONE;
}

void MLXData::caca()
{
	mlx_loop(mlx);
}

void MLXData::Draw()
{
	std::cout << "fds" << std::endl;
	// int color = 0x000000FF;
	// for (int i = 0; i < 50 * 50; ++i)
	// {
	// 	for (int j = 0; j < 50 * 50; ++j)
	// 	{
	// 		std::memcpy(&data[((i / 50) + (j / 50)) * WIDTH * 4 + ((i % 50) + (j % 50)) * 4], &color, sizeof(int));
	// 	}
	// }
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
