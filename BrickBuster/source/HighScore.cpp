#include "HighScore.h"
#include <fstream>
#include "CollisionEngine.h"
#include "Engine.h"
#include "Title.h"

HighScore::HighScore(MediaCache& mc) : State(mc), font(mediaCache.getFont(50))
{
	titleTex = mediaCache.getText("High Scores", font);
	titleTex->setPosition(mediaCache.centreX(titleTex), 5);

	menuTex = mediaCache.getText("Main Menu", font);
	menuTex->setPosition(mediaCache.centreX(menuTex), mediaCache.getScrHeight() - menuTex->getH());
}

HighScore::~HighScore()
{

}

void HighScore::enter(Engine* )
{
	loadScores();
}

void HighScore::handleEvents(SDL_Event& e, Engine* engine)
{
	mouseClicked(e, engine);
}

void HighScore::update(Engine* )
{

}

void HighScore::render(const double )
{
	mediaCache.render(titleTex);
	mediaCache.render(menuTex);

	for (const auto& s : scoresTex)
	{
		mediaCache.render(s);
	}
}

void HighScore::exit(Engine* )
{

}

#include <algorithm>
#include <iterator>

void HighScore::loadScores()
{
	std::ifstream inf("files/highscores.txt");

	if (!inf)
	{
		printf("Can't open highscores.txt");
		return;
	}

	//read the scores in from the file and put them in the hiScore vector
	std::copy(std::istream_iterator<int>(inf),
		std::istream_iterator<int>(),
		std::back_inserter(scores));

	inf.close();

	for (int i = 0; i < 10; i++)
	{
		GameTex score = mediaCache.getText(scores[i], font);
		score->setPosition(mediaCache.centreX(score), (i + 2)*score->getH());
		scoresTex.push_back(score);

	}
}

void HighScore::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (CollisionEngine::haveCollided(menuTex->getBox(), x, y))
		{
			engine->changeState(std::make_unique<Title>(mediaCache));
		}
	}
}