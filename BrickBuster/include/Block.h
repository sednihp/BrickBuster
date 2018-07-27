#pragma once
#include "Object.h"

namespace BrickBuster
{
	enum class BlockColor
	{
		RED,
		ORANGE,
		YELLOW,
		GREEN,
		BLUE,
		PURPLE
	};
}

class Block : public Object {
private:
	const int blockWidth = 80;
	const int blockHeight = 20;
	SDL_Rect box;
	SDL_Color color;
	bool destructible;
	int score;

	void setColor(BrickBuster::BlockColor bc);

public:
	Block(const Point2D& p, BrickBuster::BlockColor bc);
	~Block();

	const SDL_Rect& getBox() const { return box; }
	const SDL_Color& getColor() const { return color; }
	const int getHeight() const { return blockHeight; }
};