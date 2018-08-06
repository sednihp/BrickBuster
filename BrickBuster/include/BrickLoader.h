#pragma once
#include <vector>
#include "Brick.h"
#include <memory>

class BrickLoader {
public:
	BrickLoader() {}
	BrickLoader(const int levelNum, std::vector<std::unique_ptr<Brick>>& bricks);
	~BrickLoader() {}

	void loadBricks(const int levelNum, std::vector<std::unique_ptr<Brick>>& bricks);
};