#include "MLXData.hpp"


/*extern "C"*/ Data	*init(int width, int height, std::list<int> *snake, std::list<int> *object)
{
	return new MLXData(width, height, snake, object);
}

/*extern "C"*/ void	end(Data *data)
{
	delete data;
}
