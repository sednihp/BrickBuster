#pragma once
#include <string>

class GameException
{
private:
	std::string msg;

public:
	GameException(const std::string theErrorMsg)
	{
		msg = theErrorMsg;
	}

	std::string getErrorMsg()
	{
		return msg;
	}
};