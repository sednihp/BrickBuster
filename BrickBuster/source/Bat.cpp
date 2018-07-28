#include "Bat.h"

Bat::Bat(const int scrWidth, const int scrHeight) : color{128,64,32}
{
	setBatToStartPosition(scrWidth, scrHeight);

	position.x = box.x;
	position.y = box.y;
}

void Bat::setBatToStartPosition(const int scrWidth, const int scrHeight)
{
	box = { (scrWidth - batWidth) / 2, box.y = scrHeight - batMargin, box.w = batWidth, box.h = batHeight };
}

Bat::~Bat()
{

}

void Bat::move(const int scrWidth)
{
	position.x += direction.x * speed;

	if (position.x < 0)
	{
		position.x = 0;
	}
	else if (position.x + batWidth > scrWidth)
	{
		position.x = scrWidth - batWidth;
	}
}

void Bat::setDirection(const Vector2D& newDir)
{
	direction = newDir;
}

const SDL_Rect& Bat::getBox()
{
	box.x = static_cast<int>(position.x);
	box.y = static_cast<int>(position.y);

	return box;
}

void Bat::reset(const int scrWidth, const int scrHeight)
{
	direction = { 0,0 };
	setBatToStartPosition(scrWidth, scrHeight);
	position.x = box.x;
}

void Bat::startMoving()
{
	switch (rand() % 2)
	{
		case 0:
			direction.y = -1;
			break;
		case 1: 
			direction.y = 1;
			break;
	}
}