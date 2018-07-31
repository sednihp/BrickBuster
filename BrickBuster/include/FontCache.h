#pragma once
#include "SDL_ttf.h"
#include <map>

class FontCache
{
	private:
		SDL_Renderer* &ren;
		std::map<int, TTF_Font*> fonts;
		const std::string fontFile;

		FontCache &operator=(const FontCache&) = delete;
		FontCache(const FontCache&) = delete;

	public:
		FontCache(SDL_Renderer* &ren, const std::string &f);
		~FontCache();

		void flush();
		TTF_Font* getFont(const int size);
};