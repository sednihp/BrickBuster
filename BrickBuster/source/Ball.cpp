#include "Ball.h"

Ball::Ball(const std::string& img, const int scrWidth, const int topOfBat) : Object(img), moving(false), speed(0)
{
	position.x = ((scrWidth - ballWidth) / 2) + radius;
	position.y = topOfBat - radius;
}

Ball::~Ball()
{

}

const Point2D Ball::getPosition()
{
	return { position.x - radius, position.y - radius };
}

int Ball::move(const int scrWidth, const int scrHeight, const SDL_Rect& bat, std::vector<std::unique_ptr<Block>>& blocks, const double dTime)
{
	direction.normalize();

	//move across, then check if it's hit the bat, a block or the edge of the screen
	const double moveX = direction.x * speed * dTime;
	position.x += moveX;

	if (hasCollided(bat))
	{
		position.x -= moveX;
		direction.x *= -1;
	}

	for (auto& block : blocks)
	{
		if (hasCollided(block->getBox()))
		{
			position.x -= moveX;
			direction.x *= -1;
			block->destroyBlock();
		}
	}

	if (position.x - radius < 0)
	{
		direction.x *= -1;
	}
	else if (position.x + radius > scrWidth)
	{
		direction.x *= -1;
	}

	//move up/down then check if it's hit the bat or a block
	//if its off the bottom of the screen then return -1
	const double moveY = direction.y * speed * dTime;
	position.y += moveY;

	if (hasCollided(bat))
	{
		position.y -= moveY;
		direction.y *= -1;
	}

	for (auto& block : blocks)
	{
		if (hasCollided(block->getBox()))
		{
			position.y -= moveY;
			direction.y *= -1;
			block->destroyBlock();
		}
	}

	if (position.y - radius < 0)
	{
		direction.y *= -1;
		position.y -= moveY;
	}
	else if (position.y - radius > scrHeight)
	{
		return -1;
	}

	return 0;
}

bool Ball::hasCollided(const SDL_Rect& rect) 
{
	double closestX, closestY;

	if (position.x < rect.x)
		closestX = rect.x;
	else if (position.x > rect.x + rect.w)
		closestX = rect.x + rect.w;
	else
		closestX = position.x;

	if (position.y < rect.y)
		closestY = rect.y;
	else if (position.y > rect.y + rect.h)
		closestY = rect.y + rect.h;
	else
		closestY = position.y;

	if (distance(position.x, position.y, closestX, closestY) < radius)
		return true;

	return false;
}

const double Ball::distance(const double x1, const double y1, const double x2, const double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void Ball::startMoving(const double xDir, const double yDir)
{
	moving = true;

	const double randomX = rand() % 20 + 50;
	const double randomY = rand() % 20 + 50;

	direction.x = xDir * randomX;
	direction.y = yDir * randomY;

	speed = movingSpeed;
}

void Ball::reset(const int _x, const int scrHeight)
{
	direction = { 0,0 };
	position.x = _x + radius;
	position.y = ((scrHeight - ballWidth) / 2) + radius;
	speed = 0;
	moving = false;
}