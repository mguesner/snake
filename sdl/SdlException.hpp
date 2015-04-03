#ifndef SDLEXCEPTION_HPP
#define SDLEXCEPTION_HPP

#include <exception>

class SdlException : public std::exception
{
public:
	SdlException();
	SdlException(const char *msg);
	virtual const char* what() const throw();

private:

	const char* msg;
};

#endif
