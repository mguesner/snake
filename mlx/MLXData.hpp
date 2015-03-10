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
	void Close();
	void Lock();
	void Start();
	eInput GetInput();
	void SetInput(int);
	Windows		*win;

	~MLXData();

private:

	int			width;
	int			height;
};

#endif
