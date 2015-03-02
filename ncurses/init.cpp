#include "NCursesData.hpp"

extern "C" Data	*init(int width, int height, std::list<int> *snake, std::list<int> *object)
{
	return new NCursesData(width, height, snake, object);
}

extern "C" void	end(Data *e)
{
	(void)e;
}
