#pragma once
#include "Object.h"

class Bat : public Object {
private:
	const int speed = 7;
	const int batMargin = 50;
	const int batWidth = 80;
	const int batHeight = 20;
	SDL_Color color;
	SDL_Rect box;

	void setBatToStartPosition(const int scrWidth, const int scrHeight);
	
public:
	Bat(const int scrWidth, const int scrHeight);
	~Bat();

	const SDL_Rect& getBox();
	const SDL_Color& getColor() const { return color; }
	const int getWidth() const { return batWidth; }
	void move(const int scrWidth);
	void setDirection(const Vector2D& newDir);
	void reset(const int scrWidth, const int scrHeight);
	void startMoving();
};