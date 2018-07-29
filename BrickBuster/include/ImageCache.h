#pragma once
#include "GameTexture.h"
#include <string>
#include <map>
#include <memory>

class ImageCache
{
	private:
		SDL_Renderer* &ren;
		std::map<std::string, GameTex> images;

		ImageCache &operator=(const ImageCache&);
		ImageCache(const ImageCache&);

	public:
		ImageCache(SDL_Renderer* &renderer);
		~ImageCache();

		void flush();
		GameTex getImage(const std::string& file);
};