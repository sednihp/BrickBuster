#pragma once
#include "MediaCache.h"
#include <iostream>
class Engine;

class State
{
	private:
		State & operator=(const State&) = delete;
		State(const State&) = delete;

	protected:
		MediaCache &mediaCache;		

	public:
		State(MediaCache &mc) : mediaCache(mc) {}
		virtual ~State() {};

        virtual void enter(Engine* engine) = 0;
		virtual void handleEvents(SDL_Event& e, Engine* engine) = 0;
		virtual void update(Engine* engine) = 0;
		virtual void render(const double dt) = 0;
		virtual void exit(Engine* engine) = 0;
};