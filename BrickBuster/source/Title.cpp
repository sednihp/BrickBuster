#include "Title.h"
#include "HighScore.h"
#include "Level.h"
#include "Engine.h"
#include "Controls.h"
#include "LevelEditor.h"
#include "CollisionEngine.h"

Title::Title(MediaCache &mc) : State(mc), 
								font(mediaCache.getFont(100)),
								menuFont(mediaCache.getFont(75))
{
	generateTextures();
}

Title::~Title()
{
}

void Title::enter(Engine*)
{
}

void Title::handleEvents(SDL_Event& e, Engine* engine)
{
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

void Title::update(Engine*)
{
}

void Title::render(const double )
{
	mediaCache.render(titleTex, titleTex->getPosition());

	for(auto &item : menu)
	{
		mediaCache.render(item, item->getPosition());
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
	titleTex = mediaCache.getText("Brick Buster", font);
	titleTex->setPosition(mediaCache.centreX(titleTex->getW()), 10);

	menu.push_back(mediaCache.getText("Play", menuFont));
	//menu.push_back(mediaCache.getText("Level Editor", menuFont));
	menu.push_back(mediaCache.getText("High Scores", menuFont));
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
		if (CollisionEngine::haveCollided(menu[0]->getBox(), x, y))
		{
			engine->changeState(std::make_unique<Level>(mediaCache, 1));
		}
		else if (CollisionEngine::haveCollided(menu[1]->getBox(), x, y))
		{
			engine->changeState(std::make_unique<HighScore>(mediaCache));
			//engine->changeState(std::make_unique<EditorLevelSelector>(mediaCache));
		}
		else if (CollisionEngine::haveCollided(menu[2]->getBox(), x, y))
		{
			engine->stopRunning();
		}
	}
}