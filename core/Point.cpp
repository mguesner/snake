#include "Point.hpp"

Point::Point() {
}

Point::Point(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::Point(Point const & src) {
	x = src.x;
	y = src.y;
	z = src.z;
}

Point& Point::operator=(Point const & src) {
	x = src.x;
	y = src.y;
	z = src.z;
	return *this;
}


Point& Point::operator+=(Point const & ref)
{
	x += ref.x;
	y += ref.y;
	z += ref.z;
	x %= x;
	y %= y;
	z %= z;
	return *this;
}

Point& Point::operator-=(Point const & ref)
{
	x -= ref.x;
	y -= ref.y;
	z -= ref.z;
	return *this;
}

bool Point::operator==(Point const & ref)
{
	if (ref.x == x && ref.y == y && ref.z == z)
		return true;
	return false;
}

Point& Point::operator+(Point const & ref)
{
	x += ref.x;
	y += ref.y;
	z += ref.z;
	return *this;
}

Point& Point::operator-(Point const & ref)
{
	x -= ref.x;
	y -= ref.y;
	z -= ref.z;
	return *this;
}

Point::~Point() {
}

void	Point::UpdateZ(double coef)
{
	z *= coef;
}

void	Point::UpdateX(double coef)
{
	x *= coef;
}

void	Point::UpdateY(double coef)
{
	y *= coef;
}

int			Point::getX() {
	return this->x;
}

int			Point::getY() {
	return this->y;
}

int			Point::getZ() {
	return this->z;
}

std::ostream& operator<<(std::ostream& os, Point& pt)
{
	os << "x : "<<pt.getX() <<" y :" << pt.getY();
	return os;
}

