#include "Block.h"

Block::Block(const Point2D& p, BrickBuster::BlockColor bc) : destructible(true), alive(true)
{
	configureBlock(bc);
	position = p;

	box = { static_cast<int>(position.x), static_cast<int>(position.y), blockWidth, blockHeight };
}

Block::~Block()
{

}

void Block::configureBlock(BrickBuster::BlockColor bc)
{
	score = static_cast<int>(bc);

	switch (bc)
	{
		case BrickBuster::BlockColor::RED:
			color = { 255,0,0 };
			break;
		case BrickBuster::BlockColor::ORANGE:
			color = { 255,128,0 };
			break;
		case BrickBuster::BlockColor::YELLOW:
			color = { 255,255,0 };
			break;
		case BrickBuster::BlockColor::GREEN:
			color = { 0,255,0 };
			break;
		case BrickBuster::BlockColor::BLUE:
			color = { 0,0,255 };
			break;
		case BrickBuster::BlockColor::PURPLE:
			color = { 128,0,255 };
			break;
		case BrickBuster::BlockColor::GREY:
			color = { 192,192,192 };
			destructible = false;
			break;
	}
}

void Block::hitByBall()
{
	if (destructible)
	{
		alive = false;
	}
}