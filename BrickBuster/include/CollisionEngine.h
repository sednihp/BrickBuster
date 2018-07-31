#pragma once
#include "SDL.h"
#include "Ball.h"

namespace CollisionEngine
{
	const bool checkCollision(const SDL_Rect& box, const int x, const int y);
    const bool checkCollision(const SDL_Rect& firstBox, const SDL_Rect& secondBox);
}