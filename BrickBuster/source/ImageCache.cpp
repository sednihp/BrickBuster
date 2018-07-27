#include "ImageCache.h"
#include "SDL_image.h"
#include <iostream>
#include "Vectors.h"

ImageCache::ImageCache(SDL_Renderer* &renderer) : ren(renderer)
{
	if(SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		exit(1);
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
std::shared_ptr<GameTexture> ImageCache::getImage(const std::string& file)
{
	auto i = images.find(file);

    if(i == images.end())
    {
		SDL_Surface* loadedSurface = IMG_Load(file.c_str());
		if (!loadedSurface)
		{
			std::cout << "Emtpy surface: " << IMG_GetError() << "\n";
		}
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0, 0xFF));
		SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, loadedSurface);
		if (!tex)
		{
			std::cout << "Empty texture: " << IMG_GetError() << "\n";
		}
		auto gt = std::make_shared<GameTexture>(tex);
		i = images.insert(i, std::make_pair(file, gt));

		SDL_FreeSurface(loadedSurface);
    }

    return i->second;
}