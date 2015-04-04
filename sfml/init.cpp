#include "SFMLData.hpp"

extern "C" Data	*init(int width, int height, std::list<GameObject*> *objects)
{
	return new SFMLData(width, height, objects);
}

extern "C" void	end(Data *data)
{
	delete data;
}
