#pragma once
#include "GameTexture.h"
#include <string>
#include <map>
#include "SDL_ttf.h"
#include <memory>

class TextCache
{
	private:
		SDL_Renderer* &ren;
		std::map<std::pair<TTF_Font*, std::string>, GameTex> words;

		TextCache &operator=(const TextCache&) = delete;
		TextCache(const TextCache&) = delete;

	public:
		TextCache(SDL_Renderer* &renderer);
		~TextCache();

		void flush();
		GameTex getText(const std::string& message, TTF_Font* font, const SDL_Color& color);
		GameTex getText(const int message, TTF_Font* font, const SDL_Color& color);
};