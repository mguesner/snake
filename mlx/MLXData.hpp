#ifndef MLXDATA_HPP
#define MLXDATA_HPP

#include <Data.hpp>
#include <thread>
#include "windows.hpp"


class MLXData : public Data
{
public:
	MLXData(int width, int height, std::list<GameObject*> *objects);
	void Draw();
	void Lock();
	void Start();
	eInput GetInput();
	void SetInput(int);
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
