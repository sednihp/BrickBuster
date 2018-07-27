#pragma once
#include "Object.h"
#include "Block.h"

class Ball : public Object {
private:
	SDL_Color color;
	bool moving;
	const int ballWidth = 20;
	const int radius = ballWidth / 2;
	const int movingSpeed = 400;
	const double speedIncrement = 1.05;
	double speed;

public:
	Ball(const std::string& img, const int scrWidth, const int topOfBat);
	~Ball();

	const Point2D getPosition();
	const int getRadius() { return radius; }
	const bool isMoving() { return moving; }
	void reverseXDir() { direction.x *= -1; }

	void startMoving(const double xDir, const double yDir);
	bool hasCollided(const SDL_Rect& rect);
	const double distance(const double x1, const double y1, const double x2, const double y2);
	int move(const int scrWidth, const int scrHeight, const SDL_Rect& bat, std::vector<std::unique_ptr<Block>>& blocks, const double dTime);
	void reset(const int _x, const int scrHeight);
};