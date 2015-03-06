#include "MLXData.hpp"

void	mouse_event(int x, int y, void *e)
{
	(void)x;
	(void)y;
	(void)e;
}

void	expose_event(void *e)
{
	auto it = reinterpret_cast<MLXData *>(e);
	// int color = 0x00FF00;
	// int x = 0;
	// while (x < WIDTH * HEIGHT * 4)
	// {
	// 	std::memcpy(&it->data[x], &color, sizeof(int));
	// 	x += 4;
	// }
	mlx_put_image_to_window(it->mlx, it->win, it->img_win, 0, 0);
}

void	redraw_event(void *e)
{
	(void) e;
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
	(void)keycode;
	(void)e;

}

void	click_event(int code, int x, int y, void *e)
{
	(void)code;
	(void)x;
	(void)y;
	(void)e;
}

extern "C" Data	*init(int width, int height, std::list<GameObject*> *objects)
{
	return new MLXData(width, height, objects);
}

extern "C" void	end(Data *data)
{
	delete data;
}
