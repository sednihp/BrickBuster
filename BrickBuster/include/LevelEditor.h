#pragma once
#include "State.h"
#include "BrickManager.h"

class LevelEditor : public State {
private:
	std::unique_ptr<BrickManager> brickManager;
	TTF_Font* font;
	std::vector<GameTex> menu;
	std::unique_ptr<Brick> brick;
	BrickColour brickColour = BrickColour::PURPLE;

	void mouseClicked(SDL_Event&, Engine* engine);
	void mouseWheelScrolled(SDL_Event& e);

public:
	LevelEditor(MediaCache& mc);
	~LevelEditor();

	virtual void enter(Engine* engine);
	virtual void handleEvents(SDL_Event& e, Engine* engine);
	virtual void update(Engine* engine);
	virtual void render(const double dTime);
	virtual void exit(Engine* engine);
};