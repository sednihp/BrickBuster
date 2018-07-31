#include "Brick.h"

Brick::Brick(std::unique_ptr<InputComponent> ic,
				std::unique_ptr<GraphicsComponent> gc,
				const Point2D& p,
				BrickBuster::BrickColor bc) : GameObject(std::move(ic), 
														std::move(gc))
{
	configureBrick(bc);
	position = p;
	setBox({ static_cast<int>(position.x), static_cast<int>(position.y), blockWidth, blockHeight });
	//box = { static_cast<int>(position.x), static_cast<int>(position.y), blockWidth, blockHeight };
}

Brick::~Brick()
{
}

void Brick::configureBrick(BrickBuster::BrickColor bc)
{
	score = static_cast<int>(bc);

	switch (bc)
	{
		case BrickBuster::BrickColor::RED:
			color = { 255,0,0 };
			break;
		case BrickBuster::BrickColor::ORANGE:
			color = { 255,128,0 };
			break;
		case BrickBuster::BrickColor::YELLOW:
			color = { 255,255,0 };
			break;
		case BrickBuster::BrickColor::GREEN:
			color = { 0,255,0 };
			break;
		case BrickBuster::BrickColor::BLUE:
			color = { 0,0,255 };
			break;
		case BrickBuster::BrickColor::PURPLE:
			color = { 128,0,255 };
			break;
		case BrickBuster::BrickColor::GREY:
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