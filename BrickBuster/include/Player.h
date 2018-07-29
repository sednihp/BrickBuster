#pragma once

class Player {
private:
	int score, lives;

public:
	Player() : score(0), lives(3) {}
	~Player() {}

	void hasScored() { ++score; }
	void loseLife() { --lives; }
	
	const int getScore() const { return score; }
	const int getLives() const { return lives; }

	void reset() { score = 0; }
};