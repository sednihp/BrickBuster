#pragma once
#include "State.h"
#include <vector>

class ChooseLevel : public State {
private:
	TTF_Font * f1;
	TTF_Font* f2;
	const int numLevels = 14;
	std::vector<GameTex> levelTex;
	GameTex menu;

	void mouseClicked(SDL_Event &e, Engine* engine);

public:
	ChooseLevel(MediaCache& mc);
	~ChooseLevel();

	virtual void enter(Engine* engine);
	virtual void handleEvents(SDL_Event &e, Engine* engine);
	virtual void update(Engine* engine);
	virtual void render();
	virtual void exit(Engine* engine);
};