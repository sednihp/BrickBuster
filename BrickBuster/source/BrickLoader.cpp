#include "BrickLoader.h"
#include <fstream>
#include <iostream>
#include "InputComponent.h"

void BrickLoader::loadBricks(const int levelNum, std::vector<std::unique_ptr<Brick>>& blocks)
{
	std::string levelFile = "files/levels/" + std::to_string(levelNum) + ".lvl";

	std::ifstream infile(levelFile);
	if (!infile)
	{
		std::cerr << "Can't open " << levelNum << ".lvl";
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
		BrickBuster::BrickColor bc = static_cast<BrickBuster::BrickColor>(colour);

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

		blocks.push_back(std::make_unique<Brick>(std::make_unique<BrickInputComponent>(), 
													std::make_unique<BrickGraphicsComponent>(), 
													p, 
													bc));
	}

	infile.close();
}