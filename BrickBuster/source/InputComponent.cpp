#include "InputComponent.h"
#include "GameObject.h"

void BatInputComponent:: handleEvents(GameObject& obj, SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
		case SDLK_a:
			obj.setDirection({ -1,0 });
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			obj.setDirection({ 1,0 });
			break;
		}
	}
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
		case SDLK_a:
			obj.setDirection({ 0,0 });
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			obj.setDirection({ 0,0 });
			break;
		}
	}
}