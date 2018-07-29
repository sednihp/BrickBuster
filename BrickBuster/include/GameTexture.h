#pragma once
#include "SDL_render.h"
#include <memory>

class GameTexture;

typedef std::shared_ptr<GameTexture> GameTex;

class GameTexture 
{
	private:
		SDL_Rect box;
		SDL_Texture* tex;

	public:
		GameTexture(SDL_Texture*);
		~GameTexture();

		const int getW() const { return box.w; };
		const int getH() const { return box.h; }
		const int getX() const { return box.x; }
		const int getY() const { return box.y; }
		const SDL_Rect& getBox() const { return box; }
		SDL_Texture* texture() const { return tex; }

		void setPosition(const int x, const int y);
};