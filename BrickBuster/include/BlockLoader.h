#pragma once
#include <vector>
#include "Block.h"
#include <memory>

class BlockLoader {
public:
	BlockLoader() {}
	~BlockLoader() {}

	void loadBlocks(const int levelNum, std::vector<std::unique_ptr<Block>>& blocks);
};