#pragma once
#include "SDL.h"
#include "PowerUp.h"

namespace CollisionEngine
{
	const bool haveCollided(const SDL_Rect& box, const int x, const int y);
    const bool haveCollided(const SDL_Rect& firstBox, const SDL_Rect& secondBox);
}
