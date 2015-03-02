#include "NCursesData.hpp"

Data	*init(int width, int height, std::list<int> *snake
	, std::list<int> *objects)
{
	return new NCursesData(width, height, snake, objects);
}

void	end(Data *data)
{
	delete data;
}
