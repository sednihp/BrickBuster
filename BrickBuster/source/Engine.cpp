#include "Engine.h"
#include "Title.h"
#include <time.h>

Engine::Engine() :	running(true),
					previous(SDL_GetTicks()), lag(0.0),
					mediaCache()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	stateMachine = std::make_unique<StateMachine>(this);
	stateMachine->setCurrentState(std::make_shared<Title>(mediaCache));
}

Engine::~Engine()
{
}

void Engine::run()
{
	while(running)
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

		render();
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
			changeState(std::make_shared<Title>(mediaCache));
		}

		stateMachine->currentState()->handleEvents(e, this);
	}
}

void Engine::update()
{
	stateMachine->currentState()->update(this);
}

//clear the screen, render the currentState then update the screen
void Engine::render()
{
	mediaCache.clearScreen();

	stateMachine->currentState()->render();

	mediaCache.updateScreen();
}

void Engine::changeState(std::shared_ptr<State> newState)
{
	stateMachine->changeState(newState);
}