#include "GameTexture.h"
#include "GameException.h"

//initialize tex, then query it to find it's width and height
GameTexture::GameTexture(SDL_Texture* texture) : tex(texture)
{
	if (SDL_QueryTexture(tex, NULL, NULL, &box.w, &box.h) < 0)
	{
		std::string msg = "SDL_QueryTexture error: ";
		msg += SDL_GetError();

		GameException e(msg);
		throw e;
	}
}

GameTexture::~GameTexture()
{
	SDL_DestroyTexture(tex);
}

void GameTexture::setPosition(const int x, const int y)
{
	box.x = x;
	box.y = y;
}

void GameTexture::setPosition(const Point2D p)
{
	box.x = static_cast<int>(p.x);
	box.y = static_cast<int>(p.y);
}