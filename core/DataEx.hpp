#ifndef DATAEX_HPP
#define DATAEX_HPP

#include "Snake.hpp"
#include "Food.hpp"
#include "Serializer.hpp"

class DataEx
{
public:
	DataEx();
	DataEx(DataEx const & src);
	DataEx& operator=(DataEx const & rhs);
	~DataEx();
	Serializer Serialize(Snake *first, Snake *second, Food *food);
	void UnSerialize(Serializer serialize);
	Snake *GetSnake();
	Snake *GetSecondSnake();
	Food *GetFood();

private:
	//bool Serializable;
	Snake *snakeFirst;
	Snake *snakeSecond;
	Food  *food;

};

#endif
