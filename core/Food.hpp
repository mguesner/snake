#ifndef FOOD_HPP
#define FOOD_HPP

class Food
{
public:
	Food();
	Food(Food const & src);
	Food& operator=(Food const & rhs);
	~Food();
};

#endif
