#pragma once
#include "GameObject.h"
#include "BrickManager.h"
#include "Bat.h"

enum class BallState
{
	REGULAR,
	LARGE,
	SMALL
};

class Ball : public GameObject {
private:
	bool moving = false;
	const int regularWidth = 20;
	const int largeWidth = 30;
	const int smallWidth = 10;
	int width = regularWidth;
	int radius = width / 2;
	const double speedIncrement = 1.001;
	const double ballSpeed = 7;
	BallState state = BallState::REGULAR;

	void setToStartPosition(const int scrWidth, const double topOfBat);
	void changeState(BallState newState);

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
	int update(const int scrWidth, const int scrHeight, const std::unique_ptr<Bat>& bat, const std::vector<std::unique_ptr<Brick>>& bricks);
	void reset(const int scrWidth, const double topOfBat);
	void largeBall();
	void smallBall();
};