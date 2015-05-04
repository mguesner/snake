#ifndef LOADER_HPP
#define LOADER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "../Data.hpp"
#include "GameObject.hpp"
#include "../mp3/Sound.hpp"
#include <iostream>

class loader
{
public:
	loader();
	loader(std::string, int width, int height, std::list<GameObject*> *);
	loader(int);
	loader(loader const & src);
	loader& operator=(loader const & rhs);
	void Close();
	Data *GetData();
	Sound *GetMusic();
	~loader();
private:
	void *handle;
	Data *data = NULL;
	char *error;
	Sound* (*init_sound)(int);
	Data* (*init)(int, int, std::list<GameObject*> *object);
	Data* (*close)(Data *);
	Sound* sound;
};

#endif
