#include "CollisionEngine.h"

namespace CollisionEngine
{
	const bool haveCollided(const SDL_Rect& box, const int x, const int y)
	{
		//x is to the left of box
		if (x < box.x)
			return false;

		//x is to the right of box
		if (x > box.x + box.w)
			return false;

		//y is above box
		if (y < box.y)
			return false;

		//y is below box
		if (y > box.y + box.h)
			return false;

		return true;
	}

    const bool haveCollided(const SDL_Rect& firstBox, const SDL_Rect& secondBox)
    {
		//firstBox to the right of the second
		if (firstBox.x + firstBox.w < secondBox.x)
			return false;

		//firstBox to the left of the second
		if (firstBox.x > secondBox.x + secondBox.w)
			return false;

		//firstBox below the second
        if (firstBox.y > secondBox.y + secondBox.h)
			return false;

		//firstBox above the second
        if (firstBox.y + firstBox.h < secondBox.y)
			return false;

        return true;
    }
}
