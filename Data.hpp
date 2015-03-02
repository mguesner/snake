#ifndef DATA_HPP
#define DATA_HPP

class Data {
public:
	virtual ~Data(){}
	virtual int getTest() = 0;

protected:
	int test;
};

#endif
