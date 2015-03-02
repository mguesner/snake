#ifndef DATA_HPP
#define DATA_HPP

// extern "C"
// {
class Data
{
public:
	Data();
	Data(Data const & src);
	Data& operator=(Data const & rhs);
	~Data();
	int getTest();
private:
	int test;
};

#endif
