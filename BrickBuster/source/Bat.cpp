#include "Bat.h"
#include <iostream>

Bat::Bat(std::unique_ptr<InputComponent> ic, 
			std::unique_ptr<GraphicsComponent> gc,
			const int scrWidth, 
			const int scrHeight) : GameObject(std::move(ic), 
											std::move(gc))
{
	setColor({ 160,64,32 });
	setBatToStartPos(scrWidth, scrHeight);
	setPosition({ static_cast<double>(box.x),static_cast<double>(box.y) });
}

void Bat::setBatToStartPos(const int scrWidth, const int scrHeight)
{
	setBox({(scrWidth - batWidth) / 2, scrHeight - batMargin, batWidth, batHeight });
}

Bat::~Bat()
{

}

void Bat::update(const int scrWidth)
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
	setBox({ static_cast<int>(position.x),static_cast<int>(position.y),box.w,box.h });
	
	return box;
}

void Bat::reset(const int scrWidth, const int scrHeight)
{
	setDirection({ 0,0 });
	setBatToStartPos(scrWidth, scrHeight);
	position.x = box.x;
}

void Bat::startMoving()
{
	switch (rand() % 2)
	{
		case 0:
			setDirection({ 0,-1 });
			break;
		case 1: 
			setDirection({ 0,1 });
			break;
	}
}