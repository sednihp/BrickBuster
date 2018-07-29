#include "Level.h"
#include "CollisionEngine.h"
#include <string>
#include "Engine.h"
#include "Title.h"
#include <memory>
#include "InputComponent.h"

Level::Level(MediaCache& mc, 
			const int level) : State(mc), levelNum(level), 
								blockLoader(std::make_unique<BlockLoader>()),
								bat(std::make_unique<Bat>(std::make_unique<BatInputComponent>(), 
															std::make_unique<BatGraphicsComponent>(),
															mediaCache.getScrWidth(),
															mediaCache.getScrHeight())),
								ball(std::make_unique<Ball>(std::make_unique<BallInputComponent>(),
															std::make_unique<BallGraphicsComponent>(),
															mediaCache.getScrWidth(), 
															bat->getPosition().y))
{
	blockLoader->loadBlocks(levelNum, blocks);
}

Level::~Level()
{
}

void Level::enter(Engine* )
{

}

void Level::handleEvents(SDL_Event &e, Engine*)
{
	bat->handleEvents(e);
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
	bat->render(mediaCache);
	for (const auto& block : blocks)
	{
		block->render(mediaCache);
	}
	ball->render(mediaCache);
}

void Level::exit(Engine* )
{

}

// ===============
// ===============

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