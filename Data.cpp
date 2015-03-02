#include "Data.hpp"
// extern"C"
// {
Data::Data()
{
	test = 8;
}

Data::Data(Data const & src)
{
	(void)src;
}

Data& Data::operator=(Data const & src)
{
	(void)src;
	return *this;
}

Data::~Data()
{
}

int Data::getTest()
{
	return test;
}

