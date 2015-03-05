#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

class Point
{
	public:
		Point();
		Point(int x, int y, int z);
		Point(Point const & src);
		Point& operator=(Point const & rhs);
		~Point();

		int		getX();
		int		getY();
		int		getZ();

		void	SetX(int value);
		void	SetY(int value);
		void	SetZ(int value);
		void	UpdateX(double coef);
		void	UpdateY(double coef);
		void	UpdateZ(double coef);

		Point& operator+=(Point const & ref);
		Point& operator-=(Point const & ref);
		bool operator==(Point const & ref);
		Point& operator+(Point const & ref);
		Point& operator-(Point const & ref);
	protected:
		int		x;
		int		y;
		int		z;
};

std::ostream& operator<<(std::ostream& os, Point& pt);
#endif
