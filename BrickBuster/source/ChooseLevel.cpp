#include "ChooseLevel.h"
#include "Engine.h"
#include "Title.h"
#include"CollisionEngine.h"

ChooseLevel::ChooseLevel(MediaCache& mc) : State(mc), 
											f1(mediaCache.getFont(30)), f2(mediaCache.getFont(40))
{
	SDL_Color c = mediaCache.getTextColor();
	for(int i = 0; i < numLevels-1; i++)
	{
		std::string s = "Level " + std::to_string(i + 1);
		GameTex tex = mediaCache.getText(s, f1, c);
		tex->setPosition(mediaCache.centreX(tex->getW()), 20 + i*tex->getH());
		levelTex.push_back(tex);
	}

	GameTex userlvlTex = mediaCache.getText("User Level", f1, c);
	userlvlTex->setPosition(mediaCache.centreX(userlvlTex->getW()), 20 + (numLevels - 1)*userlvlTex->getH());
	levelTex.push_back(userlvlTex);


	menu = mediaCache.getText("Main Menu", f2, c);
	menu->setPosition(mediaCache.centreX(menu->getW()), mediaCache.getScrHeight() - menu->getH());
}

ChooseLevel::~ChooseLevel()
{

}

void ChooseLevel::enter(Engine* )
{

}

void ChooseLevel::handleEvents(SDL_Event &e, Engine* engine)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

void ChooseLevel::update(Engine* )
{

}

void ChooseLevel::render()
{
	for (const auto& tex : levelTex)
	{
		mediaCache.renderTexture(tex, tex->getX(), tex->getY());
	}

	mediaCache.renderTexture(menu, menu->getX(), menu->getY());
}

void ChooseLevel::exit(Engine* )
{

}

void ChooseLevel::mouseClicked(SDL_Event &, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (CollisionEngine::checkCollision(menu->getBox(), x, y))
		{
			engine->changeState(std::make_shared <Title> (mediaCache));
		}
	}
}