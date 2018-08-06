#include "AudioCache.h"
#include "GameException.h"
#include <iostream>

AudioCache::AudioCache() : muted(false), paused(false)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0) 
	{
		std::string msg = "SDL_INIT_AUDIO error: ";
		msg += SDL_GetError();

		GameException e(msg);
		throw e;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) 
	{
		std::string msg = "Mix_OpenAudio error: ";
		msg += Mix_GetError();
		
		GameException e(msg);
		throw e;
	}
}

AudioCache::~AudioCache()
{
	flush();

	Mix_CloseAudio();
	Mix_Quit();
}

//free all the music and sound effects from memory
void AudioCache::flush()
{
	stopMusic();
	stopChannel(-1);

	for (auto& track : music)
	{
		Mix_FreeMusic(track.second);
		track.second = nullptr;
	}
	music.clear();

	for (auto& effect : effects)
	{
		Mix_FreeChunk(effect.second);
		effect.second = nullptr;
	}
	effects.clear();
}

//look for the music file in the map
//if it's not in the map, create and add it
Mix_Music* AudioCache::getMusic(const std::string file)
{
	auto i = music.find(file);
	if (i == music.end())
	{
		Mix_Music* temp = loadMusic(file.c_str());
		i = music.insert(i, std::make_pair(file, temp));
	}

	return i->second;
}

//load the music file, if it doesn't load throw an error
Mix_Music* AudioCache::loadMusic(const std::string file)
{
	Mix_Music* temp = Mix_LoadMUS(file.c_str());

	if(temp == NULL)
	{
		std::string msg = "Mix_LoadMUS error: ";
		msg += Mix_GetError();

		GameException e(msg);
		throw e;
	}
		
	return temp;
}

//look for the effect file in the map
//if it's not in the map, create and add it
Mix_Chunk* AudioCache::getEffect(const std::string file)
{
	auto i = effects.find(file);
	if (i == effects.end())
	{
		Mix_Chunk* temp = loadEffect(file.c_str());
		i = effects.insert(i, std::make_pair(file, temp));
	}

	return i->second;
}

//load the effect file, if it doesn't load throw an error
Mix_Chunk* AudioCache::loadEffect(const std::string file)
{
	Mix_Chunk* temp = Mix_LoadWAV(file.c_str());

	if (temp == NULL)
	{
		std::string msg = "Mix_LoadWAV error: ";
		msg += Mix_GetError();

		GameException e(msg);
		throw e;
	}
		
	return temp;
}

//returns true if playing music, false if not
const bool AudioCache::isPlayingMusic()
{
	if (Mix_PlayingMusic())
	{
		return true;
	}
	else
	{
		return false;
	}
}

//play the music for the number of loops, where -1 is infinite
void AudioCache::playMusic(Mix_Music* m, const int loops)
{
	if (Mix_PlayMusic(m, loops) < 0)
	{
		std::string msg = "Mix_PlayMusic error: ";
		msg += Mix_GetError();

		GameException e(msg);
		throw e;
	}
}

//play the effect
//repeats (loops + 1) times (i.e. pass in loops = 0 to play it once)
void AudioCache::playEffect(const int channel, Mix_Chunk* effect, const int loops)
{
	if(Mix_PlayChannel(channel, effect, loops) < 0)
	{
		std::string msg = "Mix_PlayChannel error: ";
		msg += Mix_GetError();

		GameException e(msg);
		throw e;
	}
}

//stop the current music playing
void AudioCache::stopMusic()
{
	Mix_HaltMusic();
}

//stop the channel playing, -1 stops all channels
void AudioCache::stopChannel(const int channel)
{
	Mix_HaltChannel(channel);
}

//fade the music out to a stop
void AudioCache::fadeOutMusic(const int ms)
{
	if (Mix_FadeOutMusic(ms) == 0)
	{
		std::string msg = "Mix_FadeOutMusic error: ";
		msg += Mix_GetError();

		GameException e(msg);
		throw e;
	}
}

//if the cache is paused, resume everything
//otherwise pause all the channels
void AudioCache::togglePause(const int channel)
{
	if (paused)
	{
		Mix_Resume(channel);
		Mix_ResumeMusic();
	}
	else
	{
		Mix_Pause(channel);
		Mix_PauseMusic();
	}

	paused = !paused;
}

//if the cache is muted turn it back up
//otherwise set the volume to zero on all channels
void AudioCache::toggleMute()
{

	if (muted)
	{
		Mix_VolumeMusic(MIX_MAX_VOLUME);
		Mix_Volume(-1, MIX_MAX_VOLUME);
	}
	else
	{
		Mix_VolumeMusic(0);
		Mix_Volume(-1, 0);
	}

	muted = !muted;
}

//if the volume is at 0, the cache is muted
const bool AudioCache::isMuted()
{
	if (Mix_VolumeMusic(-1) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}