#include "BrickScore.h"

BrickScore::BrickScore(std::unique_ptr<InputComponent> ic, 
						std::unique_ptr<GraphicsComponent> gc, 
						const Point2D& p, const int theScore) : GameObject(std::move(ic),
																			std::move(gc)),
																startTime(SDL_GetTicks()),
																score(theScore)
{
	setPosition(p);
	setImage(std::to_string(score));
}