#include "GameException.h"
#include "ImageCache.h"
#include "SDL_image.h"
#include <iostream>
#include "Vectors.h"

ImageCache::ImageCache(SDL_Renderer* &renderer) : ren(renderer)
{
	if(SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
	{
		std::string msg = "SDL_INIT_VIDEO error: ";
		msg += SDL_GetError();

		GameException e(msg);
		throw e;
	}
}

ImageCache::~ImageCache()
{
	flush();
}

void ImageCache::flush()
{
	images.clear();
}

//look for the file in the map
//if not there, load the SDL_Texture then create a GameTexture and add it to the map
GameTex ImageCache::getImage(const std::string& file)
{
	auto i = images.find(file);

    if(i == images.end())
    {
		SDL_Surface* loadedSurface = IMG_Load(file.c_str());
		if (loadedSurface == NULL)
		{
			std::string msg = "IMG_Load error: ";
			msg += SDL_GetError();

			GameException e(msg);
			throw e;
		}
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0, 0xFF));
		SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, loadedSurface);
		if (tex == NULL)
		{
			std::string msg = "SDL_CreateTextureFromSurface error: ";
			msg += SDL_GetError();

			GameException e(msg);
			throw e;
		}
		auto gt = std::make_shared<GameTexture>(tex);
		i = images.insert(i, std::make_pair(file, gt));

		SDL_FreeSurface(loadedSurface);
    }

    return i->second;
}