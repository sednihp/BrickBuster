#include "TextCache.h"
#include "GameException.h"
#include <iostream>
#include "Vectors.h"

TextCache::TextCache(SDL_Renderer* &renderer) : ren(renderer)
{
	if (TTF_Init() == -1)
	{
		std::string msg = "TTF_Init error: ";
		msg += TTF_GetError();

		GameException e(msg);
		throw e;
	}
}

TextCache::~TextCache()
{
	flush();
}

void TextCache::flush()
{
	words.clear();
}

//make the font and message into a pair (so we can have the same message in different sizes and fonts)
//find the pair in the map
//if not there create an SDL_Surface, then an SDL_Texture and then a GameTexture
//pair the GT up with the original pair and add it to the map
GameTex TextCache::getText(const std::string& message, TTF_Font* font, const SDL_Color& color)
{
	auto pair = std::make_pair(font, message);
	auto i = words.find(pair);

	if(i == words.end())
	{
		SDL_Surface* surf = TTF_RenderText_Blended(font, message.c_str(), color);
		if (surf == NULL)
		{
			std::string msg = "TTF_RenderText_Blended error: ";
			msg += TTF_GetError();

			GameException e(msg);
			throw e;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surf);
		if (texture == NULL) 
		{
			std::string msg = "SDL_CreateTextureFromSurface error: ";
			msg += TTF_GetError();

			GameException e(msg);
			throw e;
		}
		SDL_FreeSurface(surf);
		auto gt = std::make_shared<GameTexture>(texture);

		i = words.insert(i, std::make_pair(pair, gt));
	}

    return i->second;
}

GameTex TextCache::getText(const int message, TTF_Font* font, const SDL_Color& color)
{
	return getText(std::to_string(message), font, color);
}