#include "Engine.h"
#include "GameException.h"
#include "Title.h"
#include <time.h>

Engine::Engine() :	previous(SDL_GetTicks()), lag(0.0),
					mediaCache()
{
	stateMachine = std::make_unique<StateMachine>(this, std::make_unique<Title>(mediaCache));
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
void Engine::handleEvents()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
		{
			running = false;
		}
		//the esc key takes us back to the title screen
		else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
		{
			changeState(std::make_unique<Title>(mediaCache));
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