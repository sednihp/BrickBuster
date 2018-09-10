#pragma once
#include "GameObject.h"
#include "Bat.h"
#include "Ball.h"
#include "Player.h"

enum class PowerUpType
{
	ADD_LIFE,
	LOSE_LIFE,
	LARGE_BALL,
	SMALL_BALL,
	LARGE_BAT,
	SMALL_BAT,
	SLOW_BALL,
	FAST_BALL,
	LAST
};

class PowerUp : public GameObject {
private:
	const double puSpeed = 2;
	const int width = 50;
	const int height = 10;
	bool active = true;
	PowerUpType type;

	void chooseType();

public:
	PowerUp(std::unique_ptr<InputComponent> ic, std::unique_ptr<GraphicsComponent> gc, const Point2D p);
	~PowerUp();

	virtual const SDL_Rect& getBox();
	const PowerUpType getType() const { return type; }
	const bool isActive() const { return active; }
	void collected(const std::unique_ptr<Bat>& bat, const std::unique_ptr<Ball>& ball, const std::unique_ptr<Player>& player);
	void update(const int scrHeight);
};