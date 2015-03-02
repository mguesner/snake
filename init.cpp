#include "NCursesData.hpp"

extern "C" Data	*init()
{
	return new NCursesData();
}

