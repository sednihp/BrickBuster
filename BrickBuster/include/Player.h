#pragma once

class Player {
private:
	int score, lives;

public:
	Player() : score(0), lives(5) {}
	~Player() {}

	void addScore(const int s) { score += s; }
	void loseLife() { --lives; }
	void addLife() { ++lives; }
	
	const int getScore() const { return score; }
	const int getLives() const { return lives; }

	void resetScore() { score = 0; }
	void reset() { score = 0; lives = 5; }
};