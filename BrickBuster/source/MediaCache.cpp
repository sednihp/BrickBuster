#include "MediaCache.h"
#include "GameException.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Vectors.h"

MediaCache::MediaCache() :	window(nullptr), ren(nullptr), 
							imgCache(ren), fontCache(ren, "files/fonts/LCDPHONE.TTF"), txtCache(ren)
{
	window = SDL_CreateWindow("Brick Buster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		std::string msg = "SDL_CreateWindow error: ";
		msg += SDL_GetError();

		GameException e(msg);
		throw e;
	}

	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(ren == NULL)
	{
		std::string msg = "SDL_CreateRenderer error: ";
		msg += SDL_GetError();

		GameException e(msg);
		throw e;
	}
}

MediaCache::~MediaCache()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);

    SDL_Quit();
}

GameTex MediaCache::getImage(const std::string& file)
{
	return imgCache.getImage(file);
}

TTF_Font* MediaCache::getFont(int size)
{
	return fontCache.getFont(size);
}

GameTex MediaCache::getText(const std::string& text, TTF_Font* font)
{
	return txtCache.getText(text, font, textColor);
}

GameTex MediaCache::getText(const int text, TTF_Font* font)
{
	return txtCache.getText(text, font, textColor);
}

void MediaCache::render(GameTex tex, const int x, const int y)
{
	SDL_Rect pos{ x, y, tex->getW(), tex->getH() };

	if (SDL_RenderCopy(ren, tex->getTexture(), NULL, &pos) < 0)
	{
		std::string msg = "SDL_RenderCopy error: ";
		msg += SDL_GetError();

		GameException e(msg);
		throw e;
	}
}

void MediaCache::render(GameTex tex, const Point2D& position, SDL_Rect clip)
{
	SDL_Rect renderQuad{ static_cast<int>(position.x), static_cast<int>(position.y), clip.w, clip.h };

	if (SDL_RenderCopyEx(ren, tex->getTexture(), &clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE) < 0)
	{
		std::string msg = "SDL_RenderCopyEx error: ";
		msg += SDL_GetError();

		GameException e(msg);
		throw e;
	}
}

void MediaCache::render(GameTex tex, const Point2D& position, const SDL_RendererFlip flip)
{
	SDL_Rect pos{ static_cast<int>(position.x), static_cast<int>(position.y), tex->getW(), tex->getH() };

	if (SDL_RenderCopyEx(ren, tex->getTexture(), NULL, &pos, 0.0, NULL, flip) < 0)
	{
		std::string msg = "SDL_RenderCopyEx error: ";
		msg += SDL_GetError();

		GameException e(msg);
		throw e;
	}
}

void MediaCache::render(GameTex tex, const double x, const double y)
{
	render(tex, static_cast<int>(x), static_cast<int>(y));
}

void MediaCache::render(GameTex tex, const Point2D& position)
{
	render(tex, position.x, position.y);
}

void MediaCache::render(GameTex tex)
{
	render(tex, tex->getPosition());
}

void MediaCache::render(const SDL_Rect& rect, const SDL_Color& c)
{
	if (SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, SDL_ALPHA_OPAQUE) < 0)
	{
		std::string msg = "SDL_SetRenderDrawColor error: ";
		msg += SDL_GetError();

		GameException e(msg);
		throw e;
	}

	if (SDL_RenderFillRect(ren, &rect) < 0)
	{
		std::string msg = "SDL_RenderFillRect error: ";
		msg += SDL_GetError();

		GameException e(msg);
		throw e;
	}
}

void MediaCache::clearScreen()
{ 
	if (SDL_SetRenderDrawColor(ren, bgColor.r, bgColor.g, bgColor.b, SDL_ALPHA_OPAQUE) < 0)
	{
		std::string msg = "SDL_SetRenderDrawColor error: ";
		msg += SDL_GetError();

		GameException e(msg);
		throw e;
	}
	if(SDL_RenderClear(ren) < 0)
	{
		std::string msg = "SDL_RenderClear error: ";
		msg += SDL_GetError();

		GameException e(msg);
		throw e;
	}
}

const int MediaCache::centreX(const int gtWidth) const
{
	return (SCREEN_WIDTH - gtWidth) / 2;
}

const int MediaCache::centreY(const int gtHeight) const
{
	return (SCREEN_HEIGHT - gtHeight) / 2;
}

const int MediaCache::centreX(GameTex tex) const
{
	return centreX(tex->getW());
}

const int MediaCache::centreY(GameTex tex) const
{
	return centreY(tex->getH());
}

const Point2D MediaCache::centre(GameTex tex) const
{
	return { centreX(tex->getW()), centreY(tex->getH()) };
}