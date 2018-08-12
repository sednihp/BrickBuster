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
								brickManager(std::make_unique<BrickManager>(level)),
								bat(std::make_unique<Bat>(std::make_unique<BatInputComponent>(), 
															std::make_unique<BatGraphicsComponent>(),
															mediaCache.getScrWidth(),
															mediaCache.getScrHeight())),
								ball(std::make_unique<Ball>(std::make_unique<BallInputComponent>(),
															std::make_unique<BallGraphicsComponent>(),
															mediaCache.getScrWidth(), 
															bat->getPosition().y))
{
	pausedTex = mediaCache.getText("Paused", font);
	pausedTex->setPosition(mediaCache.centreX(pausedTex->getW()), mediaCache.centreY(pausedTex->getH()));

	levelTex = mediaCache.getText("Level " + std::to_string(levelNum), font);
	levelTex->setPosition(mediaCache.centreX(levelTex->getW()), 5);

	completeTex = mediaCache.getText("Level Complete", font);
	completeTex->setPosition(mediaCache.centreX(completeTex->getW()), mediaCache.centreY(completeTex->getH()));

	playerDeadTex = mediaCache.getText("No More Lives", font);
	playerDeadTex->setPosition(mediaCache.centreX(playerDeadTex->getW()), mediaCache.centreY(playerDeadTex->getH()));

	nextLevelTex = mediaCache.getText("Next Level", font);
	nextLevelTex->setPosition(mediaCache.centreX(nextLevelTex->getW()), mediaCache.centreY(nextLevelTex->getH()) + 2*nextLevelTex->getH());
	
	restartTex = mediaCache.getText("Restart Level", font);
	restartTex->setPosition(mediaCache.centreX(restartTex->getW()), mediaCache.centreY(nextLevelTex->getH()) + 2*restartTex->getH());

	mainMenuTex = mediaCache.getText("Main Menu", font);
	mainMenuTex->setPosition(mediaCache.centreX(mainMenuTex->getW()), mediaCache.centreY(mainMenuTex->getH()) + 3*mainMenuTex->getH());
}

Level::~Level()
{
}

void Level::enter(Engine* )
{

}

void Level::handleEvents(SDL_Event& e, Engine* engine)
{
	keyPressed(e, engine);
	mouseClicked(e, engine);

	if (state == LevelState::PLAYING)
	{
		bat->handleEvents(e);
	}
}

void Level::update(Engine* )
{
	if (state == LevelState::PLAYING)
	{
		bat->update(mediaCache.getScrWidth());

		//if ball->move() returns < 0 the ball has gone off the bottom of the screen so we need to lose a life and reset
		if (ball->update(mediaCache.getScrWidth(), mediaCache.getScrHeight(), bat, brickManager->getBricks()) < 0)
		{
			bat->reset(mediaCache.getScrWidth(), mediaCache.getScrHeight());
			ball->reset(mediaCache.getScrWidth(), bat->getPosition().y);
			player->loseLife();			
		}

		player->addScore(brickManager->update(mediaCache.getScrWidth(), mediaCache.getScrHeight(), powerUps));
		updatePowerUps();
	}

	if (brickManager->isEmpty())
	{
		changeState(LevelState::COMPLETE);
	}
	else if (player->getLives() == 0)
	{
		changeState(LevelState::DEAD);
	}
}

void Level::render(const double dTime)
{
	scoreTex = mediaCache.getText(player->getScore(), font);
	mediaCache.render(scoreTex, 0, 5);

	mediaCache.render(levelTex, levelTex->getPosition());

	livesTex = mediaCache.getText(player->getLives(), font);
	mediaCache.render(livesTex, mediaCache.getScrWidth() - livesTex->getW(), 5);

	bat->render(mediaCache, dTime);

	brickManager->render(mediaCache, dTime);

	ball->render(mediaCache, dTime);
	
	for (auto& powerUp : powerUps)
	{
		powerUp->render(mediaCache, dTime);
	}

	if (state == LevelState::PAUSED)
	{
		mediaCache.render(pausedTex, pausedTex->getPosition());
	}
	else if (state == LevelState::COMPLETE)
	{
		mediaCache.render(completeTex, completeTex->getPosition());
		mediaCache.render(nextLevelTex, nextLevelTex->getPosition());
		mediaCache.render(mainMenuTex, mainMenuTex->getPosition());
	}
	else if (state == LevelState::DEAD)
	{
		mediaCache.render(playerDeadTex, playerDeadTex->getPosition());
		mediaCache.render(restartTex, restartTex->getPosition());
		mediaCache.render(mainMenuTex, mainMenuTex->getPosition());
	}
}

void Level::exit(Engine* )
{

}

// ===============
// ===============

void Level::changeState(LevelState newState)
{
	state = newState;
}

void Level::keyPressed(SDL_Event& e, Engine*)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			if (state == LevelState::PAUSED)
			{
				changeState(LevelState::PLAYING);
			}
			else if (state == LevelState::PLAYING)
			{
				changeState(LevelState::PAUSED);
			}
			break;
		}
	}
}

void Level::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (CollisionEngine::haveCollided(nextLevelTex->getBox(), x, y) || CollisionEngine::haveCollided(restartTex->getBox(), x, y))
		{
			newGameReset();
		}
		else if (CollisionEngine::haveCollided(mainMenuTex->getBox(), x, y))
		{
			if (state == LevelState::COMPLETE || state == LevelState::DEAD)
			{
				engine->changeState(std::make_unique<Title>(mediaCache));
			}
		}		
	}
}


void Level::newGameReset()
{
	player->reset();
	bat->reset(mediaCache.getScrWidth(), mediaCache.getScrHeight());
	ball->reset(mediaCache.getScrWidth(), bat->getPosition().y);
	powerUps.clear();

	if (state == LevelState::COMPLETE && levelNum < levelCount)
	{
		++levelNum;		
	}

	brickManager->loadBricks(levelNum);
	changeState(LevelState::PLAYING);
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
