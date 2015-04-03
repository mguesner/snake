#include "SdlException.hpp"

SdlException::SdlException()
{
}

SdlException::SdlException(const char *msg) : msg(msg)
{
}

const char* SdlException::what() const throw()
{
	return msg;
}
