#include "ChooseLevel.h"
#include "Engine.h"
#include "Title.h"
#include "Level.h"
#include"CollisionEngine.h"

ChooseLevel::ChooseLevel(MediaCache& mc) : State(mc), 
											lvlFont(mediaCache.getFont(40)), f2(mediaCache.getFont(50))
{
	for(int i = 0; i < numLevels; i++)
	{
		std::string s = "Level " + std::to_string(i + 1);
		GameTex tex = mediaCache.getText(s, lvlFont);
		tex->setPosition(mediaCache.centreX(tex->getW()), topMargin + i*tex->getH());
		levelTex.push_back(tex);
	}

	userLvlTex = mediaCache.getText("User Level", lvlFont);
	userLvlTex->setPosition(mediaCache.centreX(userLvlTex->getW()), topMargin + numLevels*userLvlTex->getH());
	levelTex.push_back(userLvlTex);

	menu = mediaCache.getText("Main Menu", f2);
	menu->setPosition(mediaCache.centreX(menu->getW()), mediaCache.getScrHeight() - menu->getH());
}

ChooseLevel::~ChooseLevel()
{

}

void ChooseLevel::enter(Engine* )
{

}

void ChooseLevel::handleEvents(SDL_Event& e, Engine* engine)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

void ChooseLevel::update(Engine* )
{

}

void ChooseLevel::render(const double )
{
	for (const auto& tex : levelTex)
	{
		mediaCache.render(tex, tex->getX(), tex->getY());
	}

	mediaCache.render(menu, menu->getX(), menu->getY());
}

void ChooseLevel::exit(Engine* )
{

}

void ChooseLevel::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (CollisionEngine::haveCollided(menu->getBox(), x, y))
		{
			engine->changeState(std::make_unique<Title>(mediaCache));
		}
		else if (CollisionEngine::haveCollided(userLvlTex->getBox(), x, y))
		{
			engine->changeState(std::make_unique<Level>(mediaCache, 0));
		}
		else
		{
			for (int i = 0; i < numLevels; i++)
			{
				if (CollisionEngine::haveCollided(levelTex[i]->getBox(), x, y))
				{
					engine->changeState(std::make_unique<Level>(mediaCache, i + 1));
					break;
				}
			}
		}
	}
}