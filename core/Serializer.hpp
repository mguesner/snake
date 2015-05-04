#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <cstring>
#define BUFFERSERIALIZER 65536
class Serializer
{
public:
	Serializer();
	Serializer(Serializer const & src);
	Serializer& operator=(Serializer const & rhs);
	~Serializer();
	char data[BUFFERSERIALIZER];
	int total;
	int size[20];
};

#endif
