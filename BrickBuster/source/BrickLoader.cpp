#include "BrickLoader.h"
#include "GameException.h"
#include <fstream>
#include <iostream>
#include "InputComponent.h"
#include "Engine.h"

BrickLoader::BrickLoader(const int levelNum, std::vector<std::unique_ptr<Brick>>& bricks) : gen(r())
{
	exampleBrick = std::make_unique<Brick>(std::make_unique<BrickInputComponent>(),
											std::make_unique<BrickGraphicsComponent>(),
											Point2D{ 0,0 },
											BrickColour::RED);
	createMap(levelNum, bricks);
}

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
		BrickColour bc = static_cast<BrickColour>(colour);

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

void BrickLoader::createMap(const int level, std::vector<std::unique_ptr<Brick>>& bricks)
{
	const int MAX_ROWS = 6;
	const int MAX_COLS = 13;

	const int numRows = getRandom(1, MAX_ROWS);
	int numCols = getRandom(7, MAX_COLS);
	if (numCols % 2 == 0)
	{
		++numCols;
	}

	int highestColor = std::min(static_cast<int>(BrickColour::LAST) - 1, level % 5 + 3);

	for (int y = 1; y <= numRows; ++y)
	{
		bool skipPattern = false;
		if (getRandom(0, 1) == 0)
		{
			skipPattern = true;
		}

		bool alternatePattern = false;
		if (getRandom(0, 1) == 0)
		{
			alternatePattern = true;
		}

		int alternateColor1, alternateColor2, solidColor;

		//if we're on a row with a skipping pattern we can use the grey indestructible bricks
		if (skipPattern)
		{
			alternateColor1 = getRandom(0, highestColor);
			alternateColor2 = getRandom(0, highestColor);
			solidColor = getRandom(0, highestColor);
		}
		else
		{
			alternateColor1 = getRandom(1, highestColor);
			alternateColor2 = getRandom(1, highestColor);
			solidColor = getRandom(1, highestColor);
		}

		bool skipFlag = false;
		if (getRandom(0, 1) == 0)
		{
			skipFlag = true;
		}

		bool alternateFlag = false;
		if (getRandom(0, 1) == 0)
		{
			alternateFlag = true;
		}

		for (int x = 1; x <= numCols; ++x)
		{
			if (skipPattern && skipFlag)
			{
				skipFlag = !skipFlag;
				continue;
			}
			else
			{
				skipFlag = !skipFlag;
			}

			double px = (x - 1)  * (exampleBrick->getWidth() + 20) + (MAX_COLS - numCols) * ((exampleBrick->getWidth() + 20) / 2);
			double py = 80 + (y-1) * (exampleBrick->getHeight() + 20);
			Point2D p{ px,py };
			BrickColour bc;

			if (alternatePattern && alternateFlag)
			{
				bc = static_cast<BrickColour>(alternateColor1);
				alternateFlag = !alternateFlag;
			}
			else 
			{
				bc = static_cast<BrickColour>(alternateColor2);
				alternateFlag = !alternateFlag;
			}

			if(!alternatePattern)
			{
				bc = static_cast<BrickColour>(solidColor);
			}

			bricks.push_back(std::make_unique<Brick>(std::make_unique<BrickInputComponent>(),
														std::make_unique<BrickGraphicsComponent>(),
														p,
														bc));
			
		}
	}
}

const int BrickLoader::getRandom(const int low, const int high)
{
	std::uniform_int_distribution<int> uid(low, high);

	return uid(gen);
}