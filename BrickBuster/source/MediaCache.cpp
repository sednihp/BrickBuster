#include "MediaCache.h"
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
		std::cerr << "CreateWindow error: " << SDL_GetError() << "\n";
		exit(2);
	}

	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!ren)
	{
		std::cerr << "CreateRenderer error: " << SDL_GetError() << "\n";
		exit(3);
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

GameTex MediaCache::getText(const std::string& message, TTF_Font* font, const SDL_Color& color)
{
	return txtCache.getText(message, font, color);
}

GameTex MediaCache::getText(const int message, TTF_Font* font, const SDL_Color& color)
{
	return txtCache.getText(message, font, color);
}

void MediaCache::renderTexture(GameTex tex, const int x, const int y)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
	pos.w = tex->getW();
	pos.h = tex->getH();
 
	if (SDL_RenderCopy(ren, tex->texture(), NULL, &pos) < 0)
	{
		std::cerr << "RenderCopy error: " << SDL_GetError() << "\n";
	}
}

void MediaCache::renderTexture(GameTex tex, const double x, const double y)
{
	SDL_Rect pos;
	pos.x = static_cast<int>(x);
	pos.y = static_cast<int>(y);
	pos.w = tex->getW();
	pos.h = tex->getH();

	if (SDL_RenderCopy(ren, tex->texture(), NULL, &pos) < 0)
	{
		std::cerr << "RenderCopy error: " << SDL_GetError() << "\n";
	}
}

void MediaCache::drawRectangle(const SDL_Rect& rect, const SDL_Color c)
{
	if (SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, SDL_ALPHA_OPAQUE) < 0)
	{
		std::cerr << "SetRenderDrawColor error: " << SDL_GetError() << "\n";
	}
	if (SDL_RenderFillRect(ren, &rect) < 0)
	{
		std::cerr << "RenderFillRect error: " << SDL_GetError() << "\n";
	}
}

void MediaCache::clearScreen()
{ 
	if (SDL_SetRenderDrawColor(ren, bgColor.r, bgColor.g, bgColor.b, SDL_ALPHA_OPAQUE) < 0)
	{
		std::cerr << "SetRenderDrawColor error: " << SDL_GetError() << "\n";
	}
	if(SDL_RenderClear(ren) < 0)
	{
		std::cerr << "RenderClear error: " << SDL_GetError() << "\n";
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