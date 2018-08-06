#include "BrickLoader.h"
#include "GameException.h"
#include <fstream>
#include <iostream>
#include "InputComponent.h"

void BrickLoader::loadBricks(const int levelNum, std::vector<std::unique_ptr<Brick>>& bricks)
{
	std::string levelFile = "files/levels/" + std::to_string(levelNum) + ".lvl";

	std::ifstream infile(levelFile);
	if (!infile)
	{
		std::string msg = "File " +std::to_string(levelNum) +".lvl not loaded.";
		GameException e(msg);
		throw e;
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
		BrickColor bc = static_cast<BrickColor>(colour);

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

		bricks.push_back(std::make_unique<Brick>(std::make_unique<BrickInputComponent>(), 
													std::make_unique<BrickGraphicsComponent>(), 
													p, 
													bc));
	}

	infile.close();
}