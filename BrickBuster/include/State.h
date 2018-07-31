#pragma once
#include "MediaCache.h"
class Engine;

class State
{
	protected:
		MediaCache &mediaCache;

		State &operator=(const State&) = delete;
		State(const State&) = delete;

	public:
		State(MediaCache &mc) : mediaCache(mc) {}
		virtual ~State() {};

        virtual void enter(Engine* engine) = 0;
		virtual void handleEvents(SDL_Event &e, Engine* engine) = 0;
		virtual void update(Engine* engine) = 0;
		virtual void render() = 0;
		virtual void exit(Engine* engine) = 0;
};