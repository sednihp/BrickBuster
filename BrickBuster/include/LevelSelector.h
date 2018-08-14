#pragma once
#include "State.h"
#include <vector>

enum class LevelSelectorState {
	LEVEL,
	EDITOR
};

class LevelSelector : public State {
private:
	TTF_Font* lvlFont;
	TTF_Font* f2;
	const int numLevels = 15;
	const int topMargin = 20;
	std::vector<GameTex> levelTex;
	GameTex menu;
	LevelSelectorState state;

	void mouseClicked(SDL_Event& e, Engine* engine);

public:
	LevelSelector(LevelSelectorState lss, MediaCache& mc);
	~LevelSelector();

	virtual void enter(Engine* engine);
	virtual void handleEvents(SDL_Event& e, Engine* engine);
	virtual void update(Engine* engine);
	virtual void render(const double dTime);
	virtual void exit(Engine* engine);
};