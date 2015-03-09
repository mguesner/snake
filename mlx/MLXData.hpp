#ifndef MLXDATA_HPP
#define MLXDATA_HPP

#include <Data.hpp>
#include <thread>
#include "windows.hpp"

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
	Windows		*win;

	~MLXData();

private:

	int			width;
	int			height;
};

#endif
