#pragma once
#include "State.h"
#include "Bat.h"
#include "Ball.h"
#include "Block.h"
#include "Player.h"
#include <memory>
#include <vector>

class Level : public State {
private:
	std::unique_ptr<Bat> bat;
	std::vector<std::unique_ptr<Block>> blocks;

	void keyPressed(SDL_Event &e, Engine* engine);
	
public:
	Level(MediaCache& mc);
	~Level();

	virtual void enter(Engine* engine);
	virtual void handleEvents(SDL_Event &e, Engine* engine);
	virtual void update(const double dTime, Engine* engine);
	virtual void render();
	virtual void exit(Engine* engine);
};