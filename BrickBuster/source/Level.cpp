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
								brickLoader(std::make_unique<BrickLoader>()),
								bat(std::make_unique<Bat>(std::make_unique<BatInputComponent>(), 
															std::make_unique<BatGraphicsComponent>(),
															mediaCache.getScrWidth(),
															mediaCache.getScrHeight())),
								ball(std::make_unique<Ball>(std::make_unique<BallInputComponent>(),
															std::make_unique<BallGraphicsComponent>(),
															mediaCache.getScrWidth(), 
															bat->getPosition().y))
{
	brickLoader->loadBricks(levelNum, bricks);

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
		if (ball->update(mediaCache.getScrWidth(), mediaCache.getScrHeight(), bat, bricks) < 0)
		{
			bat->reset(mediaCache.getScrWidth(), mediaCache.getScrHeight());
			ball->reset(mediaCache.getScrWidth(), bat->getPosition().y);
			player->loseLife();			
		}

		updateBricks();
		updatePowerUps();
		updateBrickScores();
	}

	if (player->getLives() == 0)
	{
		engine->changeState(std::make_unique<Title>(mediaCache));
	}
}



void Level::render()
{
	scoreTex = mediaCache.getText(player->getScore(), font);
	mediaCache.render(scoreTex, 0, 5);

	mediaCache.render(levelTex, levelTex->getX(), levelTex->getY());

	livesTex = mediaCache.getText(player->getLives(), font);
	mediaCache.render(livesTex, mediaCache.getScrWidth() - livesTex->getW(), 5);

	bat->render(mediaCache);

	for (const auto& brickScore : brickScores)
	{
		brickScore->render(mediaCache);
	}

	for (const auto& brick : bricks)
	{
		brick->render(mediaCache);
	}

	ball->render(mediaCache);
	
	for (auto& powerUp : powerUps)
	{
		powerUp->render(mediaCache);
	}

	if (paused)
	{
		mediaCache.render(pausedTex, pausedTex->getX(), pausedTex->getY());
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

//iterate through all the bricks
//if a brick is no longer alive then it has been hit, so assign it's score to the player and remove it
void Level::updateBricks()
{
	auto b = bricks.begin();
	while (b != bricks.end())
	{
		if (!(*b)->isAlive())
		{
			player->hasScored((*b)->getScore());
			if (rand() % 10 < 1)
			{
				powerUps.push_back(std::make_unique<PowerUp>(std::make_unique<PowerUpInputComponent>(),
																std::make_unique<PowerUpGraphicsComponent>(), 
																(*b)->getPosition()));
			}

			brickScores.push_back(std::make_unique<BrickScore>(std::make_unique<BrickScoreInputComponent>(),
																std::make_unique<BrickScoreGraphicsComponent>(),
																(*b)->getPosition(), (*b)->getScore()));

			b = bricks.erase(b);
		}
		else
		{
			++b;
		}
	}
}

void Level::updatePowerUps()
{
	auto p = powerUps.begin();
	while (p != powerUps.end())
	{
		if (!(*p)->isActive())
		{
			p = powerUps.erase(p);
		}
		else
		{
			(*p)->update(mediaCache.getScrHeight());

			if (CollisionEngine::haveCollided(bat->getBox(), (*p)->getBox()))
			{
				(*p)->collected(bat, ball, player);
			}
			++p;
		}
	}
}

void Level::updateBrickScores()
{
	auto b = brickScores.begin();
	while (b != brickScores.end())
	{
		if (!(*b)->isActive())
		{
			b = brickScores.erase(b);
		}
		else
		{
			++b;
		}
	}
}