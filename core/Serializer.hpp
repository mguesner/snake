#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <cstring>

class Serializer
{
public:
	Serializer();
	Serializer(Serializer const & src);
	Serializer& operator=(Serializer const & rhs);
	~Serializer();
	char data[1048576];
	int total;
	int size[20];
};

#endif
