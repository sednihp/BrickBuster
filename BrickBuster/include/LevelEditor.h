#pragma once
#include "State.h"
#include "BrickManager.h"

class LevelEditor : public State {
private:
	std::unique_ptr<BrickManager> brickManager;
	TTF_Font* font;
	std::vector<GameTex> menu;
	GameTex levelTex;
	std::unique_ptr<Brick> brick = nullptr;
	BrickColour brickColour = BrickColour::PURPLE;
	const int level;

	void mouseClicked(SDL_Event&, Engine* engine);
	void mouseWheelScrolled(SDL_Event& e);
	const Point2D getBrickPosition();
	void saveLevel();

public:
	LevelEditor(MediaCache& mc, int levelNum);
	~LevelEditor();

	virtual void enter(Engine* engine);
	virtual void handleEvents(SDL_Event& e, Engine* engine);
	virtual void update(Engine* engine);
	virtual void render(const double dt);
	virtual void exit(Engine* engine);
};