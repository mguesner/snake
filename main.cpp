#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "Data.hpp"

int main(int argc, char **argv)
{
	void *handle;
	Data *data = NULL;
	Data *data2 = NULL;
	Data* (*init)();
	char *error;

	(void) argc;
	(void) argv;
	handle = dlopen("libcurses.so", RTLD_LAZY);
	if (!handle)
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	dlerror();
	*(void **) (&init) = dlsym(handle, "init");
	*(void **)(&data2) = dlsym(handle, "Data");

	if ((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}

	data = (*init)();
	//printf("%d\n", (data2)data->getTest());
	dlclose(handle);
	exit(EXIT_SUCCESS);
}
