#pragma once
#include <string>
#include <fstream>

class GameException
{
private:
	std::string msg;

	void log()
	{
		std::ofstream out("files/GameExceptions.log", std::ios::app);
		out << msg << std::endl;
		out.close();
	}

public:
	GameException(const std::string theErrorMsg)
	{
		msg = theErrorMsg;
		log();
	}

	std::string getErrorMsg()
	{
		return msg;
	}
};