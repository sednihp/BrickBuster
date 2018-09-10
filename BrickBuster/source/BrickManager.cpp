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
	brickLoader->createMap(levelNum, bricks);
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
			if (rand() % 10 < 2)
			{
				createPowerUp(powerUps, (*b)->getPosition());
			}

			createBrickScore((*b)->getPosition(), (*b)->getScore());
				
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

void BrickManager::createBrickScore(const Point2D p, const int score)
{
	brickScores.push_back(std::make_unique<BrickScore>(std::make_unique<BrickScoreInputComponent>(),
														std::make_unique<BrickScoreGraphicsComponent>(),
														p, 
														score));
}

void BrickManager::createPowerUp(std::vector<std::unique_ptr<PowerUp>>& powerUps, const Point2D p)
{
	powerUps.push_back(std::make_unique<PowerUp>(std::make_unique<PowerUpInputComponent>(),
													std::make_unique<PowerUpGraphicsComponent>(),
													p));
}

/*void BrickManager::update(const int scrWidth, const int scrHeight)
{
	auto b = bricks.begin();
	while (b != bricks.end())
	{
		if (!(*b)->isAlive())
		{
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
}*/

void BrickManager::render(MediaCache& mc, const double dt) const
{
	for (const auto& brick : bricks)
	{
		brick->render(mc, dt);
	}

	for (const auto& score : brickScores)
	{
		score->render(mc, dt);
	}
}

//used to judge if a level is complete
//grey bricks are indestructible so we could be stuck playing forever if we use the vector empty() method
//grey bricks have a score of 0 however, so we can just total up the possible score left 
//if it's 0 we're either out of bricks or only left with grey ones
const int BrickManager::totalScoreLeft() const
{
	int score = 0;
	for (const auto& b : bricks)
	{
		score += b->getScore();
	}

	return score;
}

const bool BrickManager::isEmpty() const 
{ 
	return totalScoreLeft() == 0; 
}