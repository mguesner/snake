#include "windows.hpp"
#include "MLXData.hpp"
#include "../core/GameObject.hpp"
#include "../core/Snake.hpp"
void	mouse_event(int x, int y, void *e)
{
	(void)x;
	(void)y;
	(void)e;
}

void	expose_event(void *e)
{
	auto win = reinterpret_cast<Windows*>(e);
	//(void)win;
	mlx_put_image_to_window(win->getMlx(), win->getWin(), win->getImgWin(), 0, 0);
}

void	redraw_event(void *e)
{
	auto win = reinterpret_cast<Windows*>(e);
	
	//check here change lib throw exception
	if (win->Pipe->ShouldClose())
		throw new std::exception();
	if (win->Pipe->GetDrawInstruction() == false)
		return;
	auto state = win->Pipe->GetState();
	win->clearImg();
	if (state == MAINMENU)
		win->DrawMainMenu();
	else if (state == NM)
		win->DrawNormalMode();
	else if (state == PAUSEMENU)
		win->DrawPauseMenu();
	//mlx_put_image_to_window(win->getMlx(), win->getWin(), win->getImgWin(), 0, 0);
	win->Pipe->SetDrawFinish();
}

void	keyboard_event(int keycode, void *e)
{
	auto win = reinterpret_cast<Windows*>(e);

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

void Windows::DrawMainMenu()
{
	int color[4] = {0xFF, 0x0000FF,0x0000FF,0x0000FF };
	int entry = Pipe->GetChoice();
	color[entry + 1] = 0xFFFFFFFF;
	mlx_string_put(mlx, win, 900, 400, color[0],
		       (char*)"MENU PRINCIPALE SNAKE LOL\n");
	mlx_string_put(mlx, win, 900, 550, color[1],
		       (char*)"NEW GAME\n");
	mlx_string_put(mlx, win, 900, 650, color[2],
		       (char*)"WALL\n");
	mlx_string_put(mlx, win, 900, 750, color[3],
		       (char*)"QUIT\n");
}

void Windows::DrawPseudoMenu()
{

}

void Windows::DrawSquare(int i, int j, int color)
{
	int x = i * 10;
	int y = j * 10;
	int count = 0;
	while (count < 10)
	{
		int count2 = 0;
		while (count2 < 10)
		{
			pixelToImg(x + count, y + count2, color);
			count2++;
		}
		count++;
	}
}

void Windows::DrawNormalMode()
{
	int color = 255;
	int colorHead = 43534543;
	int colorFood = 435566;


	std::list<GameObject*> *objects = Pipe->GetGameObjects();
	for (auto i = objects->begin(); i != objects->end(); ++i)
	{
		auto type = (*i)->GetType();
		if (type == SNAKE)
		{
			auto snake = dynamic_cast<Snake *>(*i)->GetSnake();

			for (auto cel = snake.begin(); cel != snake.end(); ++cel)
			{
				if (cel == snake.begin())
					DrawSquare((*cel).getX(), (*cel).getY(), colorHead);
				else
					DrawSquare((*cel).getX(), (*cel).getY(), color);
			}
		}
		else if (type == FOOD)
		{
			Point pos = (*i)->GetPosition();
			DrawSquare(pos.getX(), pos.getY(), colorFood);
		}
	}
	mlx_put_image_to_window(mlx, win, img_win, 0, 0);
}

void Windows::DrawPauseMenu()
{
	int color[3] = {0xFF, 0x0000FF,0x0000FF};
	int entry = Pipe->GetChoice();
	color[entry] = 0xFFFFFFFF;
	mlx_string_put(mlx, win, 900, 400, color[0],
		       (char*)"Continue\n");
	mlx_string_put(mlx, win, 900, 550, color[1],
		       (char*)"Restart\n");
	mlx_string_put(mlx, win, 900, 750, color[2],
		       (char*)"QUIT\n");
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
	catch (std::exception *e)
	{
		Destroy();
	}
}
