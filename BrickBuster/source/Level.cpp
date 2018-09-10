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
									powerUpManager(std::make_unique<PowerUpManager>()),
									bat(std::make_unique<Bat>(std::make_unique<BatInputComponent>(), 
																std::make_unique<BatGraphicsComponent>(),
																mediaCache.getScrWidth(),
																mediaCache.getScrHeight())),
									ball(std::make_unique<Ball>(std::make_unique<BallInputComponent>(),
																std::make_unique<BallGraphicsComponent>(),
																mediaCache.getScrWidth(), 
																bat->getPosition().y)),
									music(mediaCache.getMusic("files/Getting it Done.mp3")), 
									hitBrick(mediaCache.getEffect("files/brick-hit.wav")), 
									hitBat(mediaCache.getEffect("files/bat-hit.wav")),
									hitWall(mediaCache.getEffect("files/wall-hit.wav"))

{
	generateTextures();
}

Level::~Level()
{
}

void Level::enter(Engine* )
{
	mediaCache.setVolume(MIX_MAX_VOLUME / 4);
	mediaCache.playMusic(music, -1);
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

		//if ball->move() returns -1 the ball has gone off the bottom of the screen so we need to lose a life and reset
		//return of 1 means we hit the bat
		//return of 2 means we hit the wall
		//play the relevant sound effects
		int update = ball->update(mediaCache.getScrWidth(), mediaCache.getScrHeight(), bat, brickManager->getBricks());
		if (update == -1)
		{
			bat->reset(mediaCache.getScrWidth(), mediaCache.getScrHeight());
			ball->reset(mediaCache.getScrWidth(), bat->getPosition().y);
			player->loseLife();			
		}
		else if (update == 1)
		{
			mediaCache.setVolume(MIX_MAX_VOLUME, 2);
			mediaCache.playEffect(2, hitBat, 0);
		}
		else if (update == 2)
		{
			mediaCache.setVolume(MIX_MAX_VOLUME, 3);
			mediaCache.playEffect(3, hitWall, 0);
		}

		int score = brickManager->update(mediaCache.getScrWidth(), mediaCache.getScrHeight(), powerUpManager->getPowerUps());
		if (score > 0)
		{
			mediaCache.setVolume(MIX_MAX_VOLUME, 1);
			mediaCache.playEffect(1, hitBrick, 0);
		}
		player->addScore(score);
		powerUpManager->update(mediaCache.getScrHeight(), ball, bat, player);
		
		if (brickManager->isEmpty())
		{
			changeState(LevelState::COMPLETE);
		}
		else if (player->getLives() == 0)
		{
			changeState(LevelState::DEAD);
		}
	}
}

void Level::render(const double dt)
{
	scoreTex = mediaCache.getText(player->getScore(), font);
	mediaCache.render(scoreTex, 0, 5);

	mediaCache.render(levelTex, levelTex->getPosition());

	livesTex = mediaCache.getText(player->getLives(), font);
	mediaCache.render(livesTex, mediaCache.getScrWidth() - livesTex->getW(), 5);

	bat->render(mediaCache, dt);

	brickManager->render(mediaCache, dt);

	ball->render(mediaCache, dt);
	
	powerUpManager->render(mediaCache, dt);

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
	mediaCache.stopMusic();
}

// ===============
// ===============

void Level::generateTextures()
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
	nextLevelTex->setPosition(mediaCache.centreX(nextLevelTex->getW()), mediaCache.centreY(nextLevelTex->getH()) + 2 * nextLevelTex->getH());

	restartTex = mediaCache.getText("Restart", font);
	restartTex->setPosition(mediaCache.centreX(restartTex->getW()), mediaCache.centreY(nextLevelTex->getH()) + 2 * restartTex->getH());

	mainMenuTex = mediaCache.getText("Main Menu", font);
	mainMenuTex->setPosition(mediaCache.centreX(mainMenuTex->getW()), mediaCache.centreY(mainMenuTex->getH()) + 3 * mainMenuTex->getH());
}

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
		case SDLK_p:
			if (state == LevelState::PAUSED)
			{
				changeState(LevelState::PLAYING);
			}
			else if (state == LevelState::PLAYING)
			{
				changeState(LevelState::PAUSED);
			}
			break;
		case SDLK_m:
			mediaCache.toggleMute();
			break;
		}
	}
}

void Level::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (state == LevelState::COMPLETE && CollisionEngine::haveCollided(nextLevelTex->getBox(), x, y))
		{
			newLevelReset();
		}
		else if (state == LevelState::DEAD && CollisionEngine::haveCollided(restartTex->getBox(), x, y))
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


void Level::newLevelReset()
{
	bat->reset(mediaCache.getScrWidth(), mediaCache.getScrHeight());
	ball->reset(mediaCache.getScrWidth(), bat->getPosition().y);
	powerUpManager->clear();

	if (state == LevelState::COMPLETE)
	{
		++levelNum;
	}

	brickManager->loadBricks(levelNum);

	levelTex = mediaCache.getText("Level " + std::to_string(levelNum), font);
	levelTex->setPosition(mediaCache.centreX(levelTex->getW()), 5);

	changeState(LevelState::PLAYING);
}

void Level::newGameReset()
{
	player->reset();
	levelNum = 1;
	newLevelReset();
}