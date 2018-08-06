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

class BrickInputComponent : public InputComponent {
public:
	virtual void handleEvents(GameObject&, SDL_Event&) {}
};

class BallInputComponent : public InputComponent {
public:
	virtual void handleEvents(GameObject&, SDL_Event&) {}
};

class PowerUpInputComponent : public InputComponent {
public:
	virtual void handleEvents(GameObject&, SDL_Event&) {}
};

class BrickScoreInputComponent : public InputComponent {
public:
	virtual void handleEvents(GameObject&, SDL_Event&) {}
};