#include "NCursesData.hpp"


extern "C" Data	*init(int width, int height, std::list<GameObject*> *object)
{
	return new NCursesData(width, height, object);
}

extern "C" void	end(Data *data)
{
	delete data;
}
