#pragma once
#include "SDL.h"
class GameObject;

class InputComponent {
public:
	virtual ~InputComponent() {}
	virtual void handleEvents(GameObject& obj, SDL_Event &e) = 0;
};

class BatInputComponent : public InputComponent {
public:
	void handleEvents(GameObject& obj, SDL_Event &e);
};

class BlockInputComponent : public InputComponent {
public:
	virtual void handleEvents(GameObject&, SDL_Event&) {}
};

class BallInputComponent : public InputComponent {
public:
	virtual void handleEvents(GameObject&, SDL_Event&) {}
};