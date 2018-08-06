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
	setBox({(scrWidth - width) / 2, scrHeight - bottomMargin, width, height });
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
	else if (position.x + width > scrWidth)
	{
		position.x = scrWidth - width;
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
	changeState(BatState::REGULAR);
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

void Bat::largeBat()
{
	changeState(BatState::LARGE);
}

void Bat::smallBat()
{
	changeState(BatState::SMALL);
}

void Bat::changeState(BatState newState)
{
	state = newState;

	switch(state)
	{ 
		case BatState::REGULAR:
			width = regularWidth;
			break;
		case BatState::LARGE:
			width = largeWidth;
			break;
		case BatState::SMALL:
			width = smallWidth;
			break;
	}

	box.w = width;
}