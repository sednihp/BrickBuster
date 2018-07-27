#pragma once
#include "Vectors.h"
#include <string>
#include "SDL.h"

class Object
{
protected:
	Point2D position;
	Vector2D direction;
	std::string image;

public:
	Object();
	Object(const std::string& img);
	~Object();

	const Point2D& getPosition() const { return position; }
	const Vector2D& getDirection() const { return direction; }
	const std::string& getImage() const { return image; }
};