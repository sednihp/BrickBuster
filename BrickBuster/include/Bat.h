#pragma once
#include "GameObject.h"

class Bat : public GameObject {
private:
	const int speed = 7;
	const int batMargin = 50;
	const int batWidth = 80;
	const int batHeight = 20;

	void setBatToStartPos(const int scrWidth, const int scrHeight);
	
public:
	Bat(std::unique_ptr<InputComponent> ic, std::unique_ptr<GraphicsComponent> gc, const int scrWidth, const int scrHeight);
	~Bat();

	virtual const SDL_Rect& getBox();
	const int getWidth() const { return batWidth; }
	void move(const int scrWidth);
	
	void reset(const int scrWidth, const int scrHeight);
	void startMoving();
};