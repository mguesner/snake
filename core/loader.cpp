#include "loader.hpp"

loader::loader()
{
}

loader::loader(std::string name, int width, int height, std::list<GameObject*> *object)
{

	handle = dlopen(name.c_str() , RTLD_LAZY);
	if (!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	dlerror();
	*(void **) (&init) = dlsym(handle, "init");

	if ((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}
	*(void **) (&close) = dlsym(handle, "end");

	if ((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}
	data = (*init)(width, height,object);
}

loader::loader(int music)
{
	handle = dlopen("mp3/sound.so" , RTLD_LAZY);
	if (!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	dlerror();
	*(void **) (&init_sound) = dlsym(handle, "dynamic_sound");

	if ((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}
	if (init_sound)
		sound = (*init_sound)(music);
	std::cout << "loading sound lib DONE" << std::endl;
}

loader::loader(loader const & src)
{
	(void)src;
}

loader& loader::operator=(loader const & src)
{
	(void)src;
	return *this;
}

void loader::Close()
{
	// (*close)(data);
	dlclose(handle);
}

Sound *loader::GetMusic()
{
	return sound;
}

Data *loader::GetData()
{
	return data;
}

loader::~loader()
{

}
