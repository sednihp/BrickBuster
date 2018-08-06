#pragma once
#include "GameObject.h"

class BrickScore : public GameObject {
private:
	unsigned int score, startTime;
	const unsigned int lifeTime = 750;
	
public:
	BrickScore(std::unique_ptr<InputComponent> ic, std::unique_ptr<GraphicsComponent> gc, const Point2D& p, const int theScore);
	~BrickScore() {}

	const bool isActive() const { return (SDL_GetTicks() - startTime) < lifeTime; }
	void update();
};