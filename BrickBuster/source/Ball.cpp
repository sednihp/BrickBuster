#include "Ball.h"

Ball::Ball(std::unique_ptr<InputComponent> ic,
			std::unique_ptr<GraphicsComponent> gc,
			const int scrWidth, 
			const double topOfBat) : GameObject(std::move(ic), 
												std::move(gc)),
										moving(false), speed(startSpeed)
{
	image = "files/images/ball/ball.bmp";
	setToStartPosition(scrWidth, topOfBat);
}

Ball::~Ball()
{

}

void Ball::setToStartPosition(const int scrWidth, const double topOfBat)
{
	position.x = ((scrWidth - ballWidth) / 2) + radius;
	position.y = topOfBat - radius;
}

const Point2D Ball::getPosition()
{
	return { position.x - radius, position.y - radius };
}

int Ball::move(const int scrWidth, const int scrHeight, const std::unique_ptr<Bat>& bat, const std::vector<std::unique_ptr<Block>>& blocks)
{
	direction.normalize();

	//move across, then check if it's hit the bat, a block or the edge of the screen
	const double moveX = direction.x * speed;
	position.x += moveX;

	if (hasCollided(bat->getBox()))
	{
		if (direction.x > 0)
		{
			position.x = bat->getPosition().x - 2*radius;
		}
		else
		{
			position.x = bat->getPosition().x + bat->getWidth() + 2*radius;
		}
		direction.x *= -1;
		direction.x += bat->getDirection().x;
		speed *= speedIncrement;
	}

	for (auto& block : blocks)
	{
		if (hasCollided(block->getBox()))
		{
			position.x -= moveX;
			direction.x *= -1;
			speed *= speedIncrement;
			block->hitByBall();
		}
	}

	if (position.x - radius < 0 || position.x + radius > scrWidth)
	{
		position.x -= moveX;
		direction.x *= -1;
	}

	//move up/down then check if it's hit the bat or a block
	//if its off the bottom of the screen then return -1
	const double moveY = direction.y * speed;
	position.y += moveY;

	if (hasCollided(bat->getBox()))
	{
		position.y = bat->getPosition().y - radius;
		direction.y = -1;
		speed *= speedIncrement;
		direction.x += bat->getDirection().x;
	}

	for (auto& block : blocks)
	{
		if (hasCollided(block->getBox()))
		{
			position.y -= moveY;
			direction.y *= -1;
			speed *= speedIncrement;
			block->hitByBall();
		}
	}

	if (position.y - radius < 0)
	{
		position.y -= moveY;
		direction.y *= -1;
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
}

void Ball::reset(const int scrWidth, const double topOfBat)
{
	direction = { 0,0 };
	setToStartPosition(scrWidth, topOfBat);
	speed = startSpeed;
	moving = false;
}