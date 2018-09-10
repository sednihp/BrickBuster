#pragma once
#include "State.h"
#include "Bat.h"
#include "Ball.h"
#include "Brick.h"
#include "Player.h"
#include <memory>
#include <vector>
#include "BrickManager.h"
#include "BrickLoader.h"
#include "PowerUpManager.h"
#include "BrickScore.h"

enum class LevelState {
	PLAYING,
	PAUSED,
	COMPLETE,
	DEAD
};

class Level : public State {
private:
	std::unique_ptr<Player> player;
	std::unique_ptr<Bat> bat;
	std::unique_ptr<Ball> ball;
	std::unique_ptr<BrickManager> brickManager;
	std::unique_ptr<PowerUpManager> powerUpManager;
	//std::vector<std::unique_ptr<PowerUp>> powerUps;	
	Mix_Music* music;
	Mix_Chunk* hitBrick;
	Mix_Chunk* hitWall;
	Mix_Chunk* hitBat;
	TTF_Font * font;
	GameTex pausedTex, levelTex, livesTex, scoreTex, completeTex, playerDeadTex, mainMenuTex, nextLevelTex, restartTex;
	int levelNum;
	LevelState state = LevelState::PLAYING;
	bool newHighScore = false;

	void generateTextures();
	void mouseClicked(SDL_Event& e, Engine* engine);
	void keyPressed(SDL_Event& e, Engine* engine);
	void changeState(LevelState newState);
	void newLevelReset();
	void newGameReset();
	
public:
	Level(MediaCache& mc, const int level);
	~Level();

	virtual void enter(Engine* engine);
	virtual void handleEvents(SDL_Event& e, Engine* engine);
	virtual void update(Engine* engine);
	virtual void render(const double dt);
	virtual void exit(Engine* engine);
};