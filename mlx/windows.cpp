#include "windows.hpp"
#include "MLXData.hpp"
void	mouse_event(int x, int y, void *e)
{
	(void)x;
	(void)y;
	(void)e;
}

void	expose_event(void *e)
{
	auto win = reinterpret_cast<Windows*>(e);
	// int color = 0x00FF00;
	// int x = 0;
	// while (x < WIDTH * HEIGHT * 4)
	// {
	// 	std::memcpy(&it->data[x], &color, sizeof(int));
	// 	x += 4;
	// }
	mlx_put_image_to_window(win->getMlx(), win->getWin(), win->getImgWin(), 0, 0);
}

void	redraw_event(void *e)
{
	auto win = reinterpret_cast<Windows*>(e);
	mlx_put_image_to_window(win->getMlx(), win->getWin(), win->getImgWin(), 0, 0);
	// auto it = reinterpret_cast<MLXData *>(e);
	// int color = 0x00FF00;
	// int x = 0;
	// while (x < WIDTH * HEIGHT * 4)
	// {
	// 	std::memcpy(&it->data[x], &color, sizeof(int));
	// 	x += 4;
	// }
	// mlx_put_image_to_window(it->mlx, it->win, it->img_win, 0, 0);
}

void	keyboard_event(int keycode, void *e)
{
	auto win = reinterpret_cast<Windows*>(e);

	std::cout << keycode << std::endl;
	win->Pipe->SetInput(keycode);

}

void	click_event(int code, int x, int y, void *e)
{
	(void)code;
	(void)x;
	(void)y;
	(void)e;
}

Windows::Windows(MLXData *mlxData)
{
	this->width = WIDTH;
	this->height = HEIGHT;
	IsAlive = true;
	if ((mlx = mlx_init()) == NULL)
		throw std::exception();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, (char*)"Snake");
	if (win == NULL)
		throw std::exception();
	img_win = mlx_new_image(mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(img_win, &ptr, &size, &dude);
	ft_handle_loop(win, mlx, this, 0);
	Pipe = mlxData;
}

Windows::Windows()
{
	this->width = WIDTH;
	this->height = HEIGHT;
	IsAlive = true;
	if ((mlx = mlx_init()) == NULL)
		throw std::exception();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, (char*)"Snake");
	if (win == NULL)
		throw std::exception();
	img_win = mlx_new_image(mlx, WIDTH, HEIGHT);
	data = mlx_get_data_addr(img_win, &ptr, &size, &dude);
	ft_handle_loop(win, mlx, this, 0);

}

Windows::Windows(std::string name, unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	char* name2 = const_cast<char*>(name.c_str());
	IsAlive = true;

	if ((mlx = mlx_init()) == NULL)
		throw std::exception();
	win = mlx_new_window(mlx, width, height, name2);
	if (win == NULL)
		throw std::exception();
	img_win = mlx_new_image(mlx, width, height);
	data = mlx_get_data_addr(img_win, &ptr, &size, &dude);
	terrain = mlx_get_data_addr(img_win, &ptr, &size, &dude);

	ft_handle_loop(win, mlx, this, 0);
}


void	Windows::pixelToImg(int x, int y, int color)
{
	if (x >= 0 && x <= width && y >= 0 && y <= height)
		std::memcpy(&data[(x * 4) + (y * 4 * width)], &color, sizeof(int));
}

void	Windows::clearImg()
{
	int color = 0;
	int x = 0;
	while (x < width *height * 4)
	{
		std::memcpy(&data[x], &color, sizeof(int));
		x +=4;
	}
}

void	Windows::Destroy()
{
	mlx_destroy_window(mlx, win);
}

Windows::~Windows()
{

}

void *Windows::getMlx()
{
	return mlx;
}

void *Windows::getImgWin()
{
	return img_win;
}

void *Windows::getWin()
{
	return win;
}

int Windows::getWidth()
{
	return width;
}


int Windows::getHeight()
{
	return height;
}

void	Windows::Run()
{
	try
	{
		mlx_loop(mlx);
	}
	catch (std::exception e)
	{
		Destroy();
		std::cout << "This is the end >"<<std::endl;
	}
}
