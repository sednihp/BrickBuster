#pragma once
#include "SDL.h"
class Object;

class InputComponent {
public:
	virtual ~InputComponent() {}
	virtual void handleEvents(Object& obj, SDL_Event &e) = 0;
};

class BatInputComponent : public InputComponent {
public:
	void handleEvents(Object& obj, SDL_Event &e);
};

class BlockInputComponent : public InputComponent {
public:
	virtual void handleEvents(Object&, SDL_Event&) {}
};

class BallInputComponent : public InputComponent {
public:
	virtual void handleEvents(Object&, SDL_Event&) {}
};