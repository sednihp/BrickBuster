#pragma once
#include "SDL.h"
#include "Ball.h"

namespace CollisionEngine
{
    const bool checkCollision(const SDL_Rect& firstBox, const SDL_Rect& secondBox);
	const bool checkCollision(const SDL_Rect& mBox, const int x, const int y);
}