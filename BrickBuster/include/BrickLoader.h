#pragma once
#include <vector>
#include "Brick.h"
#include <memory>

class BrickLoader {
public:
	BrickLoader() {}
	~BrickLoader() {}

	void loadBricks(const int levelNum, std::vector<std::unique_ptr<Brick>>& bricks);
};