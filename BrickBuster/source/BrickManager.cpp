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

void BrickManager::add(std::unique_ptr<Brick> b)
{
	bricks.push_back(std::move(b));
}

//if a brick isn't alive, get it's score and randomly create a powerup
//create the brickScore text and then erase the brick
//otherwise just move on to the next element
int BrickManager::update(const int scrWidth, const int scrHeight, std::vector<std::unique_ptr<PowerUp>>& powerUps)
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

	for (const auto& brick : bricks)
	{
		brick->update(scrWidth, scrHeight);
	}

	return score;
}

void BrickManager::update(const int scrWidth, const int scrHeight)
{
	auto b = bricks.begin();
	while (b != bricks.end())
	{
		if (!(*b)->isAlive())
		{
			std::cout << "Brick erased, score " << (*b)->getScore() << std::endl;
			b = bricks.erase(b);
		}
		else
		{
			++b;
		}
	}

	for (const auto& brick : bricks)
	{
		brick->update(scrWidth, scrHeight);
	}
}

void BrickManager::render(MediaCache& mc, const double dTime) const
{
	for (const auto& brick : bricks)
	{
		brick->render(mc, dTime);
	}

	for (const auto& score : brickScores)
	{
		score->render(mc, dTime);
	}
}