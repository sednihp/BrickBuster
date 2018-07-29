#include "Level.h"
#include "CollisionEngine.h"
#include "Engine.h"
#include "InputComponent.h"
#include "Title.h"
#include <algorithm>

Level::Level(MediaCache& mc, 
			const int level) : State(mc), 
								font(mediaCache.getFont(60)),
								levelNum(level), 
								paused(false),
								player(std::make_unique<Player>()),
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

	pausedTex = mediaCache.getText("Paused", font, mediaCache.getTextColor());
	pausedTex->setPosition(mediaCache.centreX(pausedTex->getW()), mediaCache.centreY(pausedTex->getH()));
}

Level::~Level()
{
}

void Level::enter(Engine* )
{

}

void Level::handleEvents(SDL_Event &e, Engine*)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_SPACE: 
				paused = !paused;
				break;
		}
	}

	bat->handleEvents(e);
}

void Level::update(Engine* engine)
{
	if (!paused)
	{
		bat->move(mediaCache.getScrWidth());

		checkIfBallMoving();

		if (ball->move(mediaCache.getScrWidth(), mediaCache.getScrHeight(), bat, blocks) < 0)
		{
			player->loseLife();
			if (player->getLives() == 0)
			{
				engine->changeState(std::make_shared<Title>(mediaCache));
			}
			bat->reset(mediaCache.getScrWidth(), mediaCache.getScrHeight());
			ball->reset(mediaCache.getScrWidth(), bat->getPosition().y);
		}

		removeDestroyedBlocks();
	}
}

void Level::render()
{
	bat->render(mediaCache);
	for (const auto& block : blocks)
	{
		block->render(mediaCache);
	}
	ball->render(mediaCache);

	livesTex = mediaCache.getText(player->getLives(), font, mediaCache.getTextColor());
	mediaCache.renderTexture(livesTex, mediaCache.getScrWidth() - livesTex->getW(), 5);

	if (paused)
	{
		mediaCache.renderTexture(pausedTex, pausedTex->getX(), pausedTex->getY());
	}
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
	blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [](std::unique_ptr<Block>& block) { return (!block->isAlive()); }), blocks.end());
}