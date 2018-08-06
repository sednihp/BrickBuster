#pragma once
#include "State.h"
#include "Bat.h"
#include "Ball.h"
#include "Brick.h"
#include "Player.h"
#include <memory>
#include <vector>
#include <BrickLoader.h>
#include "PowerUp.h"
#include "BrickScore.h"

class Level : public State {
private:
	std::unique_ptr<Player> player;
	std::unique_ptr<Bat> bat;
	std::unique_ptr<Ball> ball;
	std::vector<std::unique_ptr<Brick>> bricks;
	std::vector<std::unique_ptr<PowerUp>> powerUps;
	std::vector<std::unique_ptr<BrickScore>> brickScores;
	std::unique_ptr<BrickLoader> brickLoader;
	TTF_Font * font;
	GameTex pausedTex, levelTex, livesTex, scoreTex;
	int levelNum;
	bool paused = false;

	void keyPressed(SDL_Event& e, Engine* engine);
	void updateBricks();
	void updatePowerUps();
	void updateBrickScores();
	
public:
	Level(MediaCache& mc, const int level);
	~Level();

	virtual void enter(Engine* engine);
	virtual void handleEvents(SDL_Event &e, Engine* engine);
	virtual void update(Engine* engine);
	virtual void render();
	virtual void exit(Engine* engine);
};