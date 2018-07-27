#include "FontCache.h"
#include "Vectors.h"

FontCache::FontCache(SDL_Renderer* &renderer, const std::string &f) : ren(renderer), fontFile(f)
{
}

FontCache::~FontCache()
{
	flush();

	TTF_Quit();
}

void FontCache::flush()
{
	for(auto &f : fonts)
	{
		TTF_CloseFont(f.second);
		f.second = nullptr;
	}
	fonts.clear();
}

//look to see if that size font is already open
//if it isn't then open it and add it to the map
TTF_Font* FontCache::getFont(const int size)
{
	auto i = fonts.find(size);

    if(i == fonts.end())
    {
		TTF_Font* font = TTF_OpenFont(fontFile.c_str(), size);
		if(!font)
			throw TTF_GetError();
		i = fonts.insert(i, std::make_pair(size, font));
}

    return i->second;
}