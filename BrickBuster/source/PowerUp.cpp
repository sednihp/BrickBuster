#include "PowerUp.h"

PowerUp::PowerUp(std::unique_ptr<InputComponent> ic,
					std::unique_ptr<GraphicsComponent> gc,
					const Point2D p) : GameObject(std::move(ic), 
													std::move(gc))
{
	setSpeed(puSpeed);
	setPosition(p);
	box.w = width;
	box.h = height;
	setDirection({ 0,1 });
	chooseType();
}

PowerUp::~PowerUp()
{
}

void PowerUp::chooseType()
{
	int x = rand() % static_cast<int>(PowerUpType::LAST);

	switch (x)
	{
		case 0: 
			type = PowerUpType::ADD_LIFE;
			setImage("Add A Life");
			break;
		case 1: 
			type = PowerUpType::LOSE_LIFE;
			setImage("Lose A Life");
			break;
		case 2: 
			type = PowerUpType::LARGE_BALL;
			setImage("Larger Ball");
			break;
		case 3:
			type = PowerUpType::SMALL_BALL;
			setImage("Smaller Ball");
			break;
		case 4: 
			type = PowerUpType::LARGE_BAT;
			setImage("Larger Bat");
			break;
		case 5:
			type = PowerUpType::SMALL_BAT;
			setImage("Smaller Bat");
			break;
		case 6:
			type = PowerUpType::SLOW_BALL;
			setImage("Slow Ball");
			break;
		case 7:
			type = PowerUpType::FAST_BALL;
			setImage("Fast Ball");
			break;
	}
}

const SDL_Rect& PowerUp::getBox()
{
	box.x = static_cast<int>(position.x);
	box.y = static_cast<int>(position.y);

	return box;
}

void PowerUp::update(const int scrHeight)
{
	position.y += direction.y * speed;

	if (position.y > scrHeight)
	{
		active = false;
	}
}

void PowerUp::collected(const std::unique_ptr<Bat>& bat, const std::unique_ptr<Ball>& ball, const std::unique_ptr<Player>& player)
{
	switch (type)
	{
		case PowerUpType::ADD_LIFE:
			player->addLife();
			break;
		case PowerUpType::LOSE_LIFE:
			player->loseLife();
			break;
		case PowerUpType::LARGE_BALL:
			ball->largeBall();
			break;
		case PowerUpType::SMALL_BALL:
			ball->smallBall();
			break;
		case PowerUpType::LARGE_BAT:
			bat->largeBat();
			break;
		case PowerUpType::SMALL_BAT:
			bat->smallBat();
			break;
		case PowerUpType::SLOW_BALL:
			ball->slowBall();
			break;
		case PowerUpType::FAST_BALL:
			ball->fastBall();
			break;
	}

	active = false;
}