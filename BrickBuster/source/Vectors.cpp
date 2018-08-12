#include "Vectors.h"

// =======
// POINT2D
// =======
Point2D::Point2D() : x(0), y(0)
{

}

Point2D::Point2D(double _x, double _y) : x(_x), y(_y)
{

}

Point2D::Point2D(const int _x, const int _y) : x(static_cast<double>(_x)), y(static_cast<double>(_y))
{

}

void Point2D::set(double newX, double newY)
{
	x = newX;
	y = newY;
}


// ========
// VECTOR2D
// ========
Vector2D::Vector2D() : x(0), y(0)
{

}

Vector2D::Vector2D(double _x, double _y) : x(_x), y(_y)
{

}

void Vector2D::set(double newX, double newY)
{
	x = newX;
	y = newY;
}

void Vector2D::normalize()
{
	const double length = sqrt((x*x) + (y*y));

	if (length > 0)
	{
		x /= length;
		y /= length;
	}
}