#include "Serializer.hpp"

Serializer::Serializer() : data{0}, total(0) ,size{0}
{

}

Serializer::Serializer(Serializer const & src)
{
	std::memcpy(data, src.data, BUFFERSERIALIZER);
	std::memcpy(size, src.size, sizeof(int) * 20);
}

Serializer& Serializer::operator=(Serializer const & src)
{
	std::memcpy(data, src.data, BUFFERSERIALIZER);
	std::memcpy(size, src.size, sizeof(int) * 20);
	return *this;
}

Serializer::~Serializer()
{
}

