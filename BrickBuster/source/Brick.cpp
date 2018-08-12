#include "Brick.h"

Brick::Brick(std::unique_ptr<InputComponent> ic,
				std::unique_ptr<GraphicsComponent> gc,
				const Point2D& p,
				BrickColour bc) : GameObject(std::move(ic), 
											std::move(gc))
{
	configureBrick(bc);
	position = p;
	setBox({ static_cast<int>(position.x), static_cast<int>(position.y), width, height });
}

Brick::~Brick()
{
}

void Brick::configureBrick(BrickColour bc)
{
	score = static_cast<int>(bc);

	switch (bc)
	{
		case BrickColour::RED:
			color = { 255,0,0 };
			break;
		case BrickColour::ORANGE:
			color = { 255,128,0 };
			break;
		case BrickColour::YELLOW:
			color = { 255,255,0 };
			break;
		case BrickColour::GREEN:
			color = { 0,255,0 };
			break;
		case BrickColour::BLUE:
			color = { 0,0,255 };
			break;
		case BrickColour::PURPLE:
			color = { 128,0,255 };
			break;
		case BrickColour::GREY:
			color = { 192,192,192 };
			destructible = false;
			break;
	}
}

void Brick::hitByBall()
{
	if (destructible)
	{
		alive = false;
	}
}

const SDL_Rect& Brick::getBox()
{
	box.x = static_cast<int>(position.x);
	box.y = static_cast<int>(position.y);

	return box;
}

void Brick::changeColour(BrickColour bc)
{
	configureBrick(bc);
}