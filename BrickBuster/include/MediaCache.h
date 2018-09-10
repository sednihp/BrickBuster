#pragma once
#include "SDL.h"
#include <string>
#include "ImageCache.h"
#include "FontCache.h"
#include "TextCache.h"
#include "AudioCache.h"
#include "Vectors.h"

class MediaCache
{
	private:
		const int SCREEN_WIDTH = 1280;
		const int SCREEN_HEIGHT = 720;
		const SDL_Color textColor = { 255,255,255 };
		const SDL_Color bgColor = { 91,173,255 };
		SDL_Window* window;
		SDL_Renderer* ren;
		AudioCache audioCache;
		ImageCache imgCache;
		FontCache fontCache;
		TextCache txtCache;

		MediaCache &operator=(const MediaCache&) = delete;
		MediaCache(const MediaCache&) = delete;

	public:
		MediaCache();
		~MediaCache();

		//ImageCache
		GameTex getImage(const std::string& file);
		//FontCache
		TTF_Font* getFont(const int size);
		//TextCache
		GameTex getText(const std::string& text, TTF_Font* font);
		GameTex getText(const int text, TTF_Font* font);
		//AudioCache
		Mix_Music* getMusic(const std::string filename) { return audioCache.getMusic(filename); }
		Mix_Chunk* getEffect(const std::string filename) { return audioCache.getEffect(filename); }
		const bool isPlayingMusic() { return audioCache.isPlayingMusic(); }
		void playMusic(Mix_Music* m, const int loops) { audioCache.playMusic(m, loops); }
		void playEffect(const int channel, Mix_Chunk* effect, const int loops) { audioCache.playEffect(channel, effect, loops); }
		void stopMusic() { audioCache.stopMusic(); }
		void stopChannel(const int channel) { audioCache.stopChannel(channel); }
		void fadeOutMusic(const int ms) { audioCache.fadeOutMusic(ms); }
		void togglePause(const int channel) { audioCache.togglePause(channel); }
		void toggleMute() { audioCache.toggleMute(); }
		const bool isMuted() { return audioCache.isMuted(); }
		void setVolume(const int volume, const int channel = -1) { audioCache.setVolume(volume, channel); }

		void render(GameTex tex, const int x, const int y);
		void render(GameTex tex, const double x, const double y);
		void render(GameTex tex, const Point2D& position);
		void render(GameTex tex);
		void render(GameTex tex, const Point2D& position, SDL_Rect clip);
		void render(GameTex tex, const Point2D& position, const SDL_RendererFlip flip);
		void render(const SDL_Rect& rect, const SDL_Color& color);

		void clearScreen();
		void updateScreen() { SDL_RenderPresent(ren); }

		const int getScrWidth() const { return SCREEN_WIDTH; }
		const int getScrHeight() const { return SCREEN_HEIGHT; }

		const int centreX(const int gtWidth) const;
		const int centreY(const int gtHeight) const;
		const int centreX(GameTex tex) const;
		const int centreY(GameTex tex) const;
		const Point2D centre(GameTex tex) const;

		const SDL_Color& getTextColor() const { return textColor; }
};