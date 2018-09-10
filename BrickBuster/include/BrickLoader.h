#pragma once
#include <vector>
#include "Brick.h"
#include <memory>
#include <random>

class Engine;

class BrickLoader {
private:
	std::unique_ptr<Brick> exampleBrick;
	std::random_device r;
	std::mt19937 gen;

	const int getRandom(const int low, const int high);

public:
	BrickLoader() {}
	BrickLoader(const int levelNum, std::vector<std::unique_ptr<Brick>>& bricks);
	~BrickLoader() {}

	void loadBricks(const int levelNum, std::vector<std::unique_ptr<Brick>>& bricks);
	void createMap(const int level, std::vector<std::unique_ptr<Brick>>& bricks);
};