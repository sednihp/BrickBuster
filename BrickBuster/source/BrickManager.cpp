#include "BrickManager.h"
#include "PowerUp.h"

BrickManager::BrickManager(int levelNum) : brickLoader(std::make_unique<BrickLoader>(levelNum, bricks))
{

}

BrickManager::~BrickManager()
{

}

void BrickManager::loadBricks(const int levelNum)
{
	bricks.clear();
	brickLoader->loadBricks(levelNum, bricks);
}

int BrickManager::update(std::vector<std::unique_ptr<PowerUp>>& powerUps)
{
	int score = 0;

	auto b = bricks.begin();
	while (b != bricks.end())
	{
		if (!(*b)->isAlive())
		{
			score += (*b)->getScore();
			if (rand() % 10 < 9)
			{
				powerUps.push_back(std::make_unique<PowerUp>(std::make_unique<PowerUpInputComponent>(),
									std::make_unique<PowerUpGraphicsComponent>(),
									(*b)->getPosition()));
			}

			brickScores.push_back(std::make_unique<BrickScore>(std::make_unique<BrickScoreInputComponent>(),
																std::make_unique<BrickScoreGraphicsComponent>(),
																(*b)->getPosition(), (*b)->getScore()));

			b = bricks.erase(b);
		}
		else
		{
			++b;
		}
	}

	auto bs = brickScores.begin();
	while (bs != brickScores.end())
	{
		if (!(*bs)->isActive())
		{
			bs = brickScores.erase(bs);
		}
		else
		{
			++bs;
		}
	}

	return score;
}

void BrickManager::render(MediaCache& mc) const
{
	for (const auto& brick : bricks)
	{
		brick->render(mc);
	}

	for (const auto& score : brickScores)
	{
		score->render(mc);
	}
}