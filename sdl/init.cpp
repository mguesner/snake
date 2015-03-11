#include "SdlData.hpp"

extern "C" Data	*init(int width, int height, std::list<GameObject*> *objects)
{
	return new SdlData(width, height, objects);
}

extern "C" void	end(Data *data)
{
	delete data;
}
