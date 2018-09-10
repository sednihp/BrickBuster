#pragma once
#include "BrickLoader.h"
#include "BrickScore.h"
#include <memory>
#include <iterator>

class PowerUp;
class Engine;

class BrickManager {
private:
	std::vector<std::unique_ptr<Brick>> bricks;
	std::unique_ptr<BrickLoader> brickLoader;
	std::vector<std::unique_ptr<BrickScore>> brickScores;

	void createBrickScore(const Point2D p, const int score);
	void createPowerUp(std::vector<std::unique_ptr<PowerUp>>& powerUps, const Point2D p);

	const int totalScoreLeft() const;

public:
	BrickManager(int levelNum);
	~BrickManager();

	const std::vector<std::unique_ptr<Brick>>& getBricks() const { return bricks; }
	
	void loadBricks(const int levelNum);
	void add(std::unique_ptr<Brick> b);
	void clear() { bricks.clear(); }
	int update(const int scrWidth, const int scrHeight, std::vector<std::unique_ptr<PowerUp>>& powerUps);
	//void update(const int scrWidth, const int scrHeight);
	void render(MediaCache& mc, const double dt) const;
	const bool isEmpty() const;
};