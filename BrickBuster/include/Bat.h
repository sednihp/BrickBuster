#pragma once
#include "GameObject.h"

enum class BatState
{
	REGULAR,
	LARGE,
	SMALL
};

class Bat : public GameObject {
private:
	const double batSpeed = 10;
	const int bottomMargin = 50;
	const int height = 20;
	const int regularWidth = 80;
	const int largeWidth = 100;
	const int smallWidth = 60;
	int width = regularWidth;
	BatState state = BatState::REGULAR;

	void setBatToStartPos(const int scrWidth, const int scrHeight);
	void changeState(BatState newState);
	
public:
	Bat(std::unique_ptr<InputComponent> ic, std::unique_ptr<GraphicsComponent> gc, const int scrWidth, const int scrHeight);
	~Bat();

	virtual const SDL_Rect& getBox();
	const int getWidth() const { return width; }
	void largeBat();
	void smallBat();
	void update(const int scrWidth);
	void reset(const int scrWidth, const int scrHeight);
	void startMoving();
};