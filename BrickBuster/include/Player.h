#pragma once

class Player {
private:
	const int PLAYER_LIVES = 3;
	int score = 0;
	int lives = PLAYER_LIVES;

public:
	Player() {}
	~Player() {}

	void addScore(const int s) { score += s; }
	void loseLife() { --lives; }
	void addLife() { ++lives; }
	
	const int getScore() const { return score; }
	const int getLives() const { return lives; }

	void resetScore() { score = 0; }
	void reset() { score = 0; lives = PLAYER_LIVES; }
};