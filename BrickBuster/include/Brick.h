#pragma once
#include "GameObject.h"
#include "BrickBuster.h"

class Brick : public GameObject {
private:
	const int blockWidth = 80;
	const int blockHeight = 20;
	bool destructible = true;
	bool alive = true;
	int score;

	void configureBrick(BrickBuster::BrickColor bc);

public:
	Brick(std::unique_ptr<InputComponent> ic, std::unique_ptr<GraphicsComponent> gc, const Point2D& p, BrickBuster::BrickColor bc);
	~Brick();

	void hitByBall();
	const bool isAlive() const { return alive; }
	const int getScore() const { return score; }
};