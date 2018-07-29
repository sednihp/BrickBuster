#pragma once
#include "GameObject.h"
#include "BrickBuster.h"

class Block : public GameObject {
private:
	const int blockWidth = 80;
	const int blockHeight = 20;
	bool destructible, alive;
	int score;

	void configureBlock(BrickBuster::BlockColor bc);

public:
	Block(std::unique_ptr<InputComponent> ic, std::unique_ptr<GraphicsComponent> gc, const Point2D& p, BrickBuster::BlockColor bc);
	~Block();

	void hitByBall();
	const bool isAlive() const { return alive; }
};