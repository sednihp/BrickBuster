#pragma once
#include "SDL.h"
#include "SDL_mixer.h"
#include <string>
#include <map>

class AudioCache 
{
private:
	std::map<std::string, Mix_Music*> music;
	std::map<std::string, Mix_Chunk*> effects;
	bool muted, paused;

	Mix_Music* loadMusic(const std::string file);
	Mix_Chunk* loadEffect(const std::string file);

	AudioCache &operator=(const AudioCache&) = delete;
	AudioCache(const AudioCache&) = delete;

public:
	AudioCache();
	virtual ~AudioCache();

	void flush();

	Mix_Music* getMusic(const std::string filename);
	Mix_Chunk* getEffect(const std::string filename);

	const bool isPlayingMusic();
	void playMusic(Mix_Music* m, const int loops);
	void playEffect(const int channel, Mix_Chunk* effect, const int loops);
	void stopMusic();
	void stopChannel(const int channel);
	void fadeOutMusic(const int ms);

	void togglePause(const int channel);
	void toggleMute();
	const bool isMuted();
};
