#pragma once
#include "State.h"
#include <vector>

class EditorLevelSelector : public State {
private:
	TTF_Font* lvlFont;
	TTF_Font* f2;
	const int numLevels = 15;
	const int topMargin = 20;
	std::vector<GameTex> levelTex;
	GameTex menu;

	void mouseClicked(SDL_Event& e, Engine* engine);

public:
	EditorLevelSelector(MediaCache& mc);
	~EditorLevelSelector();

	virtual void enter(Engine* engine);
	virtual void handleEvents(SDL_Event& e, Engine* engine);
	virtual void update(Engine* engine);
	virtual void render(const double dt);
	virtual void exit(Engine* engine);
};