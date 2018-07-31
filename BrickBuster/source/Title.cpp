#include "Title.h"
#include "ChooseLevel.h"
#include "Level.h"
#include "Engine.h"
#include "Controls.h"
#include "CollisionEngine.h"

Title::Title(MediaCache &mc) : State(mc), 
								titleFont(mediaCache.getFont(100)),
								menuFont(mediaCache.getFont(60))
{
	generateTextures();
}

Title::~Title()
{
}

void Title::enter(Engine*)
{
}

void Title::handleEvents(SDL_Event &e, Engine* engine)
{
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

void Title::update(Engine*)
{
}

void Title::render()
{
	for (auto& title : titleTex)
	{
		mediaCache.renderTexture(title, title->getX(), title->getY());
	}

	for(auto &item : menu)
	{
		mediaCache.renderTexture(item, item->getX(), item->getY());
	}
}

void Title::exit(Engine* )
{

}

// ===============
// Class functions
// ===============

void Title::generateTextures()
{
	titleTex.push_back(mediaCache.getText("Brick", titleFont));
	titleTex.push_back(mediaCache.getText("Buster", titleFont));

	for (size_t i = 0; i < titleTex.size(); i++)
	{
		titleTex[i]->setPosition(mediaCache.centreX(titleTex[i]->getW()), 10 + i * titleTex[i]->getH());
	}

	menu.push_back(mediaCache.getText("Play", menuFont));
	menu.push_back(mediaCache.getText("Choose Level", menuFont));
	menu.push_back(mediaCache.getText("High Scores", menuFont));
	menu.push_back(mediaCache.getText("Level Editor", menuFont));
	menu.push_back(mediaCache.getText("Exit", menuFont));

	for (size_t i = 0; i<menu.size(); ++i)
	{
		menu[i]->setPosition(mediaCache.centreX(menu[i]->getW()), mediaCache.centreY(menu[0]->getW()) + i * menu[0]->getH());
	}
}


void Title::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (CollisionEngine::checkCollision(menu[0]->getBox(), x, y))
		{
			engine->changeState(std::make_unique<Level>(mediaCache, 1));
		}
		else if (CollisionEngine::checkCollision(menu[1]->getBox(), x, y))
		{
			engine->changeState(std::make_unique<ChooseLevel>(mediaCache));
		}
		else if (CollisionEngine::checkCollision(menu[2]->getBox(), x, y))
		{
			
		}
		else if (CollisionEngine::checkCollision(menu[3]->getBox(), x, y))
		{
			
		}
		else if (CollisionEngine::checkCollision(menu[4]->getBox(), x, y))
		{
			engine->stopRunning();
		}
	}
}