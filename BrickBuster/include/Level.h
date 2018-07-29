#pragma once
#include "State.h"
#include "Bat.h"
#include "Ball.h"
#include "Block.h"
#include "Player.h"
#include <memory>
#include <vector>
#include <BlockLoader.h>

class Level : public State {
private:
	std::unique_ptr<Player> player;
	std::unique_ptr<Bat> bat;
	std::vector<std::unique_ptr<Block>> blocks;
	std::unique_ptr<Ball> ball;
	std::unique_ptr<BlockLoader> blockLoader;
	TTF_Font * font;
	GameTex pausedTex, livesTex, scoreTex;
	int levelNum;
	bool paused;

	void checkIfBallMoving();
	void removeDestroyedBlocks();
	
public:
	Level(MediaCache& mc, const int level);
	~Level();

	virtual void enter(Engine* engine);
	virtual void handleEvents(SDL_Event &e, Engine* engine);
	virtual void update(Engine* engine);
	virtual void render();
	virtual void exit(Engine* engine);
};