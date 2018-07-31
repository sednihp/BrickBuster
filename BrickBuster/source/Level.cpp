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
								player(std::make_unique<Player>()),
								blockLoader(std::make_unique<BrickLoader>()),
								bat(std::make_unique<Bat>(std::make_unique<BatInputComponent>(), 
															std::make_unique<BatGraphicsComponent>(),
															mediaCache.getScrWidth(),
															mediaCache.getScrHeight())),
								ball(std::make_unique<Ball>(std::make_unique<BallInputComponent>(),
															std::make_unique<BallGraphicsComponent>(),
															mediaCache.getScrWidth(), 
															bat->getPosition().y))
{
	blockLoader->loadBricks(levelNum, blocks);

	pausedTex = mediaCache.getText("Paused", font);
	pausedTex->setPosition(mediaCache.centreX(pausedTex->getW()), mediaCache.centreY(pausedTex->getH()));

	levelTex = mediaCache.getText("Level " + std::to_string(levelNum), font);
	levelTex->setPosition(mediaCache.centreX(levelTex->getW()), 5);
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

	if (!paused)
	{
		bat->handleEvents(e);
	}
}

void Level::update(Engine* engine)
{
	if (!paused)
	{
		bat->update(mediaCache.getScrWidth());

		//if ball->move() returns < 0 the ball has gone off the bottom of the screen so we need to lose and life and reset
		//if we've lost all our lives then we're dead
		if (ball->update(mediaCache.getScrWidth(), mediaCache.getScrHeight(), bat, blocks) < 0)
		{
			player->loseLife();
			if (player->getLives() == 0)
			{
				engine->changeState(std::make_unique<Title>(mediaCache));
			}
			bat->reset(mediaCache.getScrWidth(), mediaCache.getScrHeight());
			ball->reset(mediaCache.getScrWidth(), bat->getPosition().y);
		}

		updateBricks();
	}
}

void Level::render()
{
	scoreTex = mediaCache.getText(player->getScore(), font);
	mediaCache.renderTexture(scoreTex, 0, 5);

	mediaCache.renderTexture(levelTex, levelTex->getX(), levelTex->getY());

	livesTex = mediaCache.getText(player->getLives(), font);
	mediaCache.renderTexture(livesTex, mediaCache.getScrWidth() - livesTex->getW(), 5);

	bat->render(mediaCache);
	for (const auto& block : blocks)
	{
		block->render(mediaCache);
	}
	ball->render(mediaCache);

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

void Level::keyPressed(SDL_Event& e, Engine*)
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
}

//iterate through all the blocks
//if a block is not alive then it has been hit, so assign it's score to the player and remove it
void Level::updateBricks()
{
	auto b = blocks.begin();
	while (b != blocks.end())
	{
		if (!(*b)->isAlive())
		{
			player->hasScored((*b)->getScore());
			b = blocks.erase(b);
		}
		else
		{
			++b;
		}
	}
}