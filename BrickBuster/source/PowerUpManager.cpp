#include "PowerUpManager.h"
#include "CollisionEngine.h"

PowerUpManager::PowerUpManager()
{

}

PowerUpManager::~PowerUpManager()
{

}

void PowerUpManager::update(const int scrHeight, const std::unique_ptr<Ball>& ball, const std::unique_ptr<Bat>& bat, const std::unique_ptr<Player>& player)
{
	auto p = powerUps.begin();
	while (p != powerUps.end())
	{
		if (!(*p)->isActive())
		{
			p = powerUps.erase(p);
		}
		else
		{
			(*p)->update(scrHeight);

			if (CollisionEngine::haveCollided(bat->getBox(), (*p)->getBox()))
			{
				(*p)->collected(bat, ball, player);
			}
			++p;
		}
	}
}

void PowerUpManager::render(MediaCache& mc, const double dt) const
{
	for (const auto& powerUp : powerUps)
	{
		powerUp->render(mc, dt);
	}
}