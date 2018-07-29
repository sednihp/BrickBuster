#include "Bat.h"
#include <iostream>

Bat::Bat(std::unique_ptr<InputComponent> ic, 
			std::unique_ptr<GraphicsComponent> gc,
			const int scrWidth, 
			const int scrHeight) : Object(std::move(ic), 
											std::move(gc))
{
	color = { 160,64,32 };
	setBatToStartPos(scrWidth, scrHeight);
	position.x = box.x;
	position.y = box.y;
}

void Bat::setBatToStartPos(const int scrWidth, const int scrHeight)
{
	box = {(scrWidth - batWidth) / 2, scrHeight - batMargin, batWidth, batHeight };
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

const SDL_Rect& Bat::getBox()
{
	box.x = static_cast<int>(position.x);
	box.y = static_cast<int>(position.y);

	return box;
}

void Bat::reset(const int scrWidth, const int scrHeight)
{
	direction = { 0,0 };
	setBatToStartPos(scrWidth, scrHeight);
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