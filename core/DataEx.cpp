#include "DataEx.hpp"

DataEx::DataEx()
{
	snakeFirst = NULL;
	snakeSecond = NULL;
	food = NULL;
}

DataEx::DataEx(DataEx const & src)
{
	snakeFirst = src.snakeFirst;
	snakeSecond = src.snakeSecond;
	food = src.food;
}

DataEx& DataEx::operator=(DataEx const & src)
{
	snakeFirst = src.snakeFirst;
	snakeSecond = src.snakeSecond;
	food = src.food;
	return *this;
}

DataEx::~DataEx()
{

}

Serializer DataEx::Serialize(Snake *first, Snake *second, Food *food)
{
	Serializer serialize;
	auto firstPlayer = first->GetSnake();

	serialize.size[0] = firstPlayer.size();
	int total = 0;
	auto it = firstPlayer.begin();

	while (it != firstPlayer.end())
	{

		serialize.data[total] = (*it).getX();
		total += sizeof(double);
		serialize.data[total] = (*it).getY();
		total += sizeof(double);
		serialize.data[total] = (*it).getZ();
		total += sizeof(double);
		it++;
	}
	if (second)
	{
		auto secondPlayer = second->GetSnake();
		serialize.size[1] = secondPlayer.size();
		auto it2 = secondPlayer.begin();
		while (it2 != secondPlayer.end())
		{
			serialize.data[total] = (*it2).getX();
			total += sizeof(double);
			serialize.data[total] = (*it2).getY();
			total += sizeof(double);
			serialize.data[total] = (*it2).getZ();
			total += sizeof(double);
			it2++;
		}
	}
	if (food)
	{
		Point test = food->GetPosition();
		serialize.data[total] = test.getX();
		total += sizeof(double);
		serialize.data[total] = test.getY();
		total += sizeof(double);
		serialize.data[total] = test.getZ();
		total += sizeof(double);
	}
	serialize.total = total;
	return serialize;

}

void DataEx::UnSerialize(Serializer serialize)
{

	snakeFirst = new Snake();
	snakeSecond = new Snake();
	std::list<Point> mySnake;
	std::list<Point> yourSnake;
	int total = 0;

	int size = serialize.size[0];
	int i = 0;
	while (i < size)
	{
		double x = serialize.data[total];
		total += sizeof(double);
		double y = serialize.data[total];
		total += sizeof(double);
		double z = serialize.data[total];
		total += sizeof(double);

		Point test(x, y,z);
		mySnake.push_back(test);
		i++;
	}

	size = serialize.size[1];
	i = 0;
	while (i < size)
	{
		double x = serialize.data[total];
		total += sizeof(double);
		double y = serialize.data[total];
		total += sizeof(double);
		double z = serialize.data[total];
		total += sizeof(double);

		Point test(x, y,z);
		yourSnake.push_back(test);
		i++;
	}
	snakeFirst->SetSnake(mySnake);
	snakeSecond->SetSnake(yourSnake);
	double x = serialize.data[total];
	total += sizeof(double);
	double y = serialize.data[total];
	total += sizeof(double);
	double z = serialize.data[total];
	total += sizeof(double);
	Point test(x, y,z);
	food = new Food();
	food->SetPosition(test);
}

Snake *DataEx::GetSnake()
{
	return snakeFirst;
}

Snake *DataEx::GetSecondSnake()
{
	return snakeSecond;
}

Food *DataEx::GetFood()
{
	return food;
}
