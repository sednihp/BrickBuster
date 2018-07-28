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
	SDL_Rect box;
	SDL_Color color;
	bool destructible, alive;
	int score;

	void configureBlock(BrickBuster::BlockColor bc);

public:
	Block(const Point2D& p, BrickBuster::BlockColor bc);
	~Block();

	const SDL_Rect& getBox() const { return box; }
	const SDL_Color& getColor() const { return color; }
	const int getHeight() const { return blockHeight; }
	void hitByBall();
	const bool isAlive() const { return alive; }
};