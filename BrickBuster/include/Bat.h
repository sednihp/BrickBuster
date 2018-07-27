#pragma once
#include "Object.h"

class Bat : public Object {
private:
	const int speed = 300;
	const int batMargin = 50;
	const int batWidth = 80;
	const int batHeight = 20;
	SDL_Color color;
	SDL_Rect box;
	
public:
	Bat(const int scrWidth, const int scrHeight);
	~Bat();

	const SDL_Rect& getBox();
	const SDL_Color& getColor() const { return color; }
	const int getWidth() const { return batWidth; }
	void move(const int scrWidth, const double deltaTime);
	void setDirection(const Vector2D& newDir);
	void reset(const int scrHeight);
	void startMoving();
};