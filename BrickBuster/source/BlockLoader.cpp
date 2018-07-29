#include "BlockLoader.h"
#include <fstream>
#include <iostream>
#include "InputComponent.h"

void BlockLoader::loadBlocks(const int levelNum, std::vector<std::unique_ptr<Block>>& blocks)
{
	std::string levelFile = "files/levels/" + std::to_string(levelNum) + ".lvl";

	std::ifstream infile(levelFile);
	if (!infile)
	{
		std::cout << "Can't open " << levelNum << ".lvl";
		levelFile = "files/levels/1.lvl";
		infile.open(levelFile);
	}

	infile.seekg(0, std::ios::beg);
	bool eof = false;
	while (!eof)
	{
		int colour;
		infile >> colour;
		if (infile.eof())
		{
			eof = true;
		}
		BrickBuster::BlockColor bc = static_cast<BrickBuster::BlockColor>(colour);

		double x, y;
		infile >> x;
		if (infile.eof())
		{
			eof = true;
		}
		
		infile >> y;
		if (infile.eof())
		{
			eof = true;
		}

		Point2D p{ x,y };

		blocks.push_back(std::make_unique<Block>(std::make_unique<BlockInputComponent>(), 
													std::make_unique<BlockGraphicsComponent>(), 
													p, 
													bc));
	}

	infile.close();
}