#include "Level.h"
#include "CollisionEngine.h"
#include <string>
#include "Engine.h"
#include "Title.h"
#include <memory>

Level::Level(MediaCache& mc, 
			const int level) : State(mc), levelNum(level), blockLoader(std::make_unique<BlockLoader>()),
								bat(std::make_unique<Bat>(mediaCache.getScrWidth(), mediaCache.getScrHeight())),
								ball(std::make_unique<Ball>("files/images/ball/ball.bmp", mediaCache.getScrWidth(), bat->getPosition().y))
{
	blockLoader->loadBlocks(levelNum, blocks);
}

Level::~Level()
{
}

void Level::enter(Engine* )
{

}

void Level::handleEvents(SDL_Event &e, Engine* engine)
{
	keyPressed(e, engine);
}

void Level::update(Engine* )
{
	bat->move(mediaCache.getScrWidth());

	checkIfBallMoving();
	if (ball->move(mediaCache.getScrWidth(), mediaCache.getScrHeight(), bat->getBox(), blocks) < 0)
	{
		bat->reset(mediaCache.getScrWidth(), mediaCache.getScrHeight());
		ball->reset(mediaCache.getScrWidth(), bat->getPosition().y);
	}

	removeDestroyedBlocks();
}

void Level::render()
{
	mediaCache.drawRectangle(bat->getBox(), bat->getColor());
	for (const auto& block : blocks)
	{
		mediaCache.drawRectangle(block->getBox(), block->getColor());
	}
	mediaCache.renderTexture(mediaCache.getImage(ball->getImage()), ball->getPosition().x, ball->getPosition().y);
}

void Level::exit(Engine* )
{

}

// ===============
// ===============

void Level::keyPressed(SDL_Event &e, Engine*)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_LEFT:
			case SDLK_a:
				bat->setDirection({ -1,0 });
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				bat->setDirection({ 1,0 });
				break;
		}
	}
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_LEFT:
			case SDLK_a:
				bat->setDirection({ 0,0 });
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				bat->setDirection({ 0,0 });
				break;
		}
	}
}

void Level::checkIfBallMoving()
{
	if (!ball->isMoving() && bat->getDirection().x != 0)
	{
		ball->startMoving(bat->getDirection().x, -1);
	}
}

void Level::removeDestroyedBlocks()
{
	auto b = blocks.begin();
	while (b != blocks.end())
	{
		if (!(*b)->isAlive())
		{
			b = blocks.erase(b);
		}
		else
		{
			++b;
		}
	}
}