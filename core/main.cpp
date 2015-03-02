#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "../Data.hpp"
#include "loader.hpp"

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cout << "Usage ./nibbler width height (4 min and 1000 max)" << std::endl;
		return (EXIT_FAILURE);
	}
	loader	*graph = new loader("libcurses.so");

}
