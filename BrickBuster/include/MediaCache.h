#pragma once
#include "SDL.h"
#include <string>
#include "ImageCache.h"
#include "FontCache.h"
#include "TextCache.h"

class MediaCache
{
	private:
		const int mScrWidth = 600;
		const int mScrHeight = 750;
		SDL_Window* window;
		SDL_Renderer* ren;
		const SDL_Color textColor{ 255,255,255 };
		const SDL_Color bgColor{ 91,173,255 };

		ImageCache imgCache;
		FontCache fontCache;
		TextCache txtCache;

		MediaCache &operator=(const MediaCache&) = delete;
		MediaCache(const MediaCache&) = delete;

	public:
		MediaCache();
		~MediaCache();

		GameTex getImage(const std::string& file);
		TTF_Font* getFont(const int size);
		GameTex getText(const std::string& message, TTF_Font* font, const SDL_Color& color);
		GameTex getText(const int message, TTF_Font* font, const SDL_Color& color);

		void renderTexture(GameTex tex, const int x, const int y);
		void renderTexture(GameTex tex, const double x, const double y);
		void drawRectangle(const SDL_Rect& rect, const SDL_Color color);

		void clearScreen();
		void updateScreen();

		const int getScrWidth() const { return mScrWidth; }
		const int getScrHeight() const { return mScrHeight; }
		const int centreX(const int gtWidth) const;
		const int centreY(const int gtHeight) const;
		const SDL_Color& getTextColor();	
};