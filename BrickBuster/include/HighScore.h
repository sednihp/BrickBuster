#pragma once
#include "State.h"

class HighScore : public State {
private:
	TTF_Font * font;
	GameTex titleTex, menuTex;
	std::vector<GameTex> scoresTex;
	std::vector<int> scores;

	void loadScores();
	void mouseClicked(SDL_Event& e, Engine* engine);

public:
	HighScore(MediaCache& mc);
	~HighScore();

	virtual void enter(Engine* engine) override;
	virtual void handleEvents(SDL_Event& e, Engine* engine) override;
	virtual void update(Engine* engine) override;
	virtual void render(const double dt) override;
	virtual void exit(Engine* engine) override;
};