#include "Brick.h"

BrickColour& operator++(BrickColour &c) {
	c = static_cast<BrickColour>(static_cast<int>(c) + 1);
	if (c == BrickColour::LAST)
		c = static_cast<BrickColour>(0);
	return c;
}

BrickColour operator++(BrickColour &c, int) {
	BrickColour result = c;
	++c;
	return result;
}

BrickColour& operator--(BrickColour &c) {
	c = static_cast<BrickColour>(static_cast<int>(c) - 1);
	if (c == BrickColour::FIRST)
		c = static_cast<BrickColour>(static_cast<int>(BrickColour::LAST) - 1);
	return c;
}

BrickColour operator--(BrickColour &c, int) {
	BrickColour result = c;
	--c;
	return result;
}

std::ostream& operator<< (std::ostream& os, const BrickColour& bc)
{
	os << static_cast<int>(bc);
	return os;
}