#include "Engine.h"
#include "GameException.h"
#include "Title.h"
#include <time.h>

Engine::Engine() :	previous(SDL_GetTicks()), lag(0.0),
					mediaCache(),
					music(mediaCache.getMusic("files/Getting it Done.mp3"))
{
	stateMachine = std::make_unique<StateMachine>(this, std::make_unique<Title>(mediaCache));
	mediaCache.setVolume(MIX_MAX_VOLUME / 4);
	mediaCache.playMusic(music, -1);
}

Engine::~Engine()
{
}

void Engine::run()
{
	try
	{
		while (running)
		{
			double current = SDL_GetTicks();
			double elapsed = current - previous;
			previous = current;
			lag += elapsed;

			handleEvents();
			if (!running)
				break;

			while (lag >= frameLength)
			{
				update();
				lag -= frameLength;
			}

			render(lag / frameLength);
		}
	}
	catch (GameException e)
	{
		throw e;
	}
}

//handle any events that happen (keyboard, mouse etc) locally first, then pass them down to the currentState
//m will always toggle the mute and escape will always take us back to the main title screen
void Engine::handleEvents()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
		{
			running = false;
		}

		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_m:
				mediaCache.toggleMute();
				break;
			case SDLK_ESCAPE:
				changeState(std::make_unique<Title>(mediaCache));
				break;
			}
		}

		stateMachine->getCurrentState()->handleEvents(e, this);
	}
}

void Engine::update()
{
	stateMachine->getCurrentState()->update(this);
}

void Engine::render(const double dt)
{
	mediaCache.clearScreen();

	stateMachine->getCurrentState()->render(dt);

	mediaCache.updateScreen();
}

void Engine::changeState(std::unique_ptr<State> newState)
{
	stateMachine->changeState(std::move(newState));
}