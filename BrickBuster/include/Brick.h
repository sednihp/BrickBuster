#pragma once
#include "GameObject.h"

enum class BrickColor
{
	GREY = 0,
	PURPLE,
	BLUE,
	GREEN,
	YELLOW,
	ORANGE,
	RED
};

class Brick : public GameObject {
private:
	const int width = 80;
	const int height = 20;
	bool destructible = true;
	bool alive = true;
	int score;

	void configureBrick(BrickColor bc);

public:
	Brick(std::unique_ptr<InputComponent> ic, std::unique_ptr<GraphicsComponent> gc, const Point2D& p, BrickColor bc);
	~Brick();

	void hitByBall();
	const bool isAlive() const { return alive; }
	const int getScore() const { return score; }
};