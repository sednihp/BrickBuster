#pragma once
#include "SDL.h"
#include <string>
#include "ImageCache.h"
#include "FontCache.h"
#include "TextCache.h"
#include "Vectors.h"

class MediaCache
{
	private:
		const int mScrWidth = 1000;
		const int mScrHeight = 750;
		const SDL_Color textColor = { 255,255,255 };
		const SDL_Color bgColor = { 91,173,255 };
		SDL_Window* window;
		SDL_Renderer* ren;
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
		GameTex getText(const std::string& text, TTF_Font* font);
		GameTex getText(const int text, TTF_Font* font);

		void render(GameTex tex, const int x, const int y);
		void render(GameTex tex, const double x, const double y);
		void render(GameTex tex, const Point2D& position);
		void render(const SDL_Rect& rect, const SDL_Color& color);

		void clearScreen();
		void updateScreen() { SDL_RenderPresent(ren); }

		const int getScrWidth() const { return mScrWidth; }
		const int getScrHeight() const { return mScrHeight; }
		const int centreX(const int gtWidth) const;
		const int centreY(const int gtHeight) const;
		const SDL_Color& getTextColor() const { return textColor; }
};