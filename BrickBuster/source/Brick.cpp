#include "Brick.h"

Brick::Brick(std::unique_ptr<InputComponent> ic,
				std::unique_ptr<GraphicsComponent> gc,
				const Point2D& p,
				BrickColour bc) : GameObject(std::move(ic), 
											std::move(gc))
{
	setSpeed(brickSpeed);
	configureBrick(bc);
	position = p;
	setBox({ static_cast<int>(position.x), static_cast<int>(position.y), width, height });
}

Brick::~Brick()
{
}

void Brick::configureBrick(BrickColour bc)
{
	brickColour = bc;
	score = static_cast<int>(bc);
	destructible = true;

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
		case BrickColour::TEAL:
			setDirection({ 0,1 });
			color = { 16,150,150 };
			break;
		case BrickColour::WHITE:
			setDirection({ 1,0 });
			color = { 255,255,255 };
			break;
	}
}

void Brick::update(const int scrWidth, const int scrHeight)
{
	if (brickColour == BrickColour::TEAL)
	{
		position.y += direction.y * speed;

		if (position.y < 0)
		{
			direction.y *= -1;
			position.y = 0;
		}
		else if (position.y + height > scrHeight)
		{
			direction.y *= -1;
			position.y = scrHeight - height;
		}
	}
	else if (brickColour == BrickColour::WHITE)
	{
		position.x += direction.x * speed;

		if (position.x < 0)
		{
			direction.x *= -1;
			position.x = 0;
		}
		else if (position.x + width > scrWidth)
		{
			direction.x *= -1;
			position.x = scrWidth - width;
		}
	}
}

void Brick::hitByBall()
{
	if (destructible)
	{
		std::cout << "Brick destroyed, score: " << score << std::endl;
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