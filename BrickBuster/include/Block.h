#pragma once
#include "Object.h"

namespace BrickBuster
{
	enum class BlockColor
	{
		GREY = 0,
		PURPLE,
		BLUE,
		GREEN,
		YELLOW,
		ORANGE,
		RED
	};
}

class Block : public Object {
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