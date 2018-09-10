#pragma once
#include "SDL_render.h"
#include <memory>
#include <iostream>
#include <string>
#include "Vectors.h"

class GameTexture;

typedef std::shared_ptr<GameTexture> GameTex;

class GameTexture 
{
	private:
		SDL_Rect box = { 0,0,1,1 };
		SDL_Texture* tex;

	public:
		GameTexture(SDL_Texture*);
		~GameTexture();

		const int getW() const { return box.w; };
		const int getH() const { return box.h; }
		const int getX() const { return box.x; }
		const int getY() const { return box.y; }
		const Point2D getPosition() { return { box.x, box.y }; }
		const SDL_Rect& getBox() const { return box; }
		SDL_Texture* getTexture() const { return tex; }

		void setPosition(const int x, const int y);
};