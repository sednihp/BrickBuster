#pragma once
#include "GameObject.h"
#include "Block.h"

class Ball : public GameObject {
private:
	bool moving;
	const int ballWidth = 20;
	const int radius = ballWidth / 2;
	const double speedIncrement = 1.005;
	const double startSpeed = 7;
	double speed;

	void setToStartPosition(const int scrWidth, const double topOfBat);

public:
	Ball(std::unique_ptr<InputComponent> ic, 
			std::unique_ptr<GraphicsComponent> gc, 
			const int scrWidth, 
			const double topOfBat);
	~Ball();

	virtual const Point2D getPosition();
	const bool isMoving() const { return moving; }
	void startMoving(const double xDir, const double yDir);
	bool hasCollided(const SDL_Rect& rect);
	const double distance(const double x1, const double y1, const double x2, const double y2);
	int move(const int scrWidth, const int scrHeight, const SDL_Rect& bat, std::vector<std::unique_ptr<Block>>& blocks);
	void reset(const int scrWidth, const double topOfBat);
};