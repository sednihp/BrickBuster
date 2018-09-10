#pragma once
#include "PowerUp.h"

class PowerUpManager {
private:
	std::vector<std::unique_ptr<PowerUp>> powerUps;

public:
	PowerUpManager();
	~PowerUpManager();

	std::vector<std::unique_ptr<PowerUp>>& getPowerUps() { return powerUps; }

	void update(const int scrHeight, const std::unique_ptr<Ball>& ball, const std::unique_ptr<Bat>& bat, const std::unique_ptr<Player>& player);
	void clear() { powerUps.clear(); }
	void render(MediaCache& mc, const double dt) const;
};