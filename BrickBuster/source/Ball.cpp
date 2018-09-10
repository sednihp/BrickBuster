#include "Ball.h"

Ball::Ball(std::unique_ptr<InputComponent> ic,
			std::unique_ptr<GraphicsComponent> gc,
			const int scrWidth, 
			const double topOfBat) : GameObject(std::move(ic), 
												std::move(gc))
{
	setSpeed(ballSpeed);
	setImage("files/images/ball/ball.bmp");
	setToStartPosition(scrWidth, topOfBat);
}

Ball::~Ball()
{

}

void Ball::setToStartPosition(const int scrWidth, const double topOfBat)
{
	position.x = ((scrWidth - width) / 2) + radius;
	position.y = topOfBat - radius;
}

const Point2D Ball::getPosition()
{
	return { position.x - radius, position.y - radius };
}

int Ball::update(const int scrWidth, const int scrHeight, const std::unique_ptr<Bat>& bat, const std::vector<std::unique_ptr<Brick>>& bricks)
{
	bool hitWall = false, hitBat = false;

	if (!isMoving() && bat->getDirection().x != 0)
	{
		startMoving(bat->getDirection().x, -1);
		return 0;
	}
	else
	{
		direction.normalize();

		//move across, then check if it's hit the bat, a brick or the edge of the screen
		const double moveX = direction.x * speed;
		position.x += moveX;

		if (hasCollided(bat->getBox()))
		{
			if (direction.x > 0)
			{
				position.x = bat->getPosition().x - 2 * radius;
			}
			else
			{
				position.x = bat->getPosition().x + bat->getWidth() + 2 * radius;
			}
			direction.x *= -1;
			direction.x += bat->getDirection().x;
			direction.y = -1;
			speed *= speedIncrement;
			hitBat = true;
		}

		for (auto& brick : bricks)
		{
			if (hasCollided(brick->getBox()))
			{
				position.x -= moveX;
				direction.x *= -1;
				speed *= speedIncrement;
				brick->hitByBall();
			}
		}

		if (position.x - radius < 0 || position.x + radius > scrWidth)
		{
			position.x -= moveX;
			direction.x *= -1;
			hitWall = true;
		}

		//move up/down then check if it's hit the bat or a brick
		//if the ball is off the bottom of the screen return -1
		const double moveY = direction.y * speed;
		position.y += moveY;

		if (hasCollided(bat->getBox()))
		{
			position.y = bat->getPosition().y - 2 * radius;
			direction.y = -1;
			speed *= speedIncrement;
			direction.x += bat->getDirection().x;
			hitBat = true;
		}

		for (auto& brick : bricks)
		{
			if (hasCollided(brick->getBox()))
			{
				position.y -= moveY;
				direction.y *= -1;
				speed *= speedIncrement;
				brick->hitByBall();
			}
		}

		if (position.y - radius < 0)
		{
			position.y -= moveY;
			direction.y *= -1;
			hitWall = true;
		}
		else if (position.y - radius > scrHeight)
		{
			return -1;
		}
	}

	if (hitBat)
	{
		return 1;
	}
	else if (hitWall)
	{
		return 2;
	}
	else 
	{
		return 0;
	}
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

	const double xRand = rand() % 100 + 10;
	const double yRand = rand() % 100 + 10;

	direction.x = xDir * xRand;
	direction.y = yDir * yRand;
}

void Ball::reset(const int scrWidth, const double topOfBat)
{
	changeState(BallState::REGULAR);
	direction = { 0,0 };
	setToStartPosition(scrWidth, topOfBat);
	setSpeed(ballSpeed);
	moving = false;
}

void Ball::largeBall()
{
	changeState(BallState::LARGE);
}

void Ball::smallBall()
{
	changeState(BallState::SMALL);
}

void Ball::slowBall()
{
	speed /= 1.25;
}

void Ball::fastBall()
{
	speed *= 1.2;
}

void Ball::changeState(BallState newState)
{
	state = newState;

	switch (state)
	{
		case BallState::REGULAR:
			width = regularWidth;
			setImage("files/images/ball/ball.bmp");
			break;
		case BallState::LARGE:
			width = largeWidth;
			setImage("files/images/ball/large_ball.bmp");
			break;
		case BallState::SMALL:
			width = smallWidth;
			setImage("files/images/ball/small_ball.bmp");
			break;
	}

	radius = width / 2;
}