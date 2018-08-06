#include "MediaCache.h"
#include "GameException.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Vectors.h"

MediaCache::MediaCache() :	window(nullptr), ren(nullptr), 
							imgCache(ren), fontCache(ren, "files/fonts/LCDPHONE.TTF"), txtCache(ren)
{
	window = SDL_CreateWindow("Brick Buster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mScrWidth, mScrHeight, SDL_WINDOW_SHOWN);
	if(!window)
	{
		std::string msg = "SDL_CreateWindow error: ";
		msg += SDL_GetError();
		GameException e(msg);
		throw e;
	}

	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!ren)
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
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
	pos.w = tex->getW();
	pos.h = tex->getH();
 
	if (SDL_RenderCopy(ren, tex->texture(), NULL, &pos) < 0)
	{
		std::string msg = "SDL_RenderCopy error: ";
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
	render(tex, static_cast<int>(position.x), static_cast<int>(position.y));
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

void MediaCache::updateScreen() 
{ 
	SDL_RenderPresent(ren); 
}

const int MediaCache::centreX(const int gtWidth) const
{
	return (mScrWidth - gtWidth) / 2;
}

const int MediaCache::centreY(const int gtHeight) const
{
	return (mScrHeight - gtHeight) / 2;
}

const SDL_Color& MediaCache::getTextColor()
{
	return textColor;
}