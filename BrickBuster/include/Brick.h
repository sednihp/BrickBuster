#pragma once
#include "GameObject.h"

enum class BrickColour
{
	FIRST = -1,
	GREY = 0,
	PURPLE,
	BLUE,
	GREEN,
	YELLOW,
	ORANGE,
	RED,
	LAST
};

BrickColour& operator++(BrickColour &c);
BrickColour operator++(BrickColour &c, int);
BrickColour& operator--(BrickColour &c);
BrickColour operator--(BrickColour &c, int);

class Brick : public GameObject {
private:
	const int width = 80;
	const int height = 20;
	bool destructible = true;
	bool alive = true;
	int score;

	void configureBrick(BrickColour bc);

public:
	Brick(std::unique_ptr<InputComponent> ic, std::unique_ptr<GraphicsComponent> gc, const Point2D& p, BrickColour bc);
	~Brick();

	virtual const SDL_Rect& getBox();
	void hitByBall();
	void changeColour(BrickColour bc);
	const bool isAlive() const { return alive; }
	const int getScore() const { return score; }
	const int getWidth() const { return width; }
	const int getHeight() const { return height; }
};