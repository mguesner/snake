#ifndef LOADER_HPP
#define LOADER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "../Data.hpp"
#include <iostream>

class loader
{
public:
	loader();
	loader(std::string, int width, int height, std::list<int> *snake, std::list<int> *object);
	loader(loader const & src);
	loader& operator=(loader const & rhs);
	void Close();
	Data *GetData();
	~loader();
private:
	void *handle;
	Data *data = NULL;
	char *error;
	Data* (*init)(int , int , std::list<int> *snake, std::list<int> *object);
	Data* (*close)(Data *);
};

#endif
