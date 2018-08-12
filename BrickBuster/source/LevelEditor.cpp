#include "LevelEditor.h"
#include "CollisionEngine.h"
#include "Engine.h"
#include "Title.h"

LevelEditor::LevelEditor(MediaCache& mc) :State(mc), 
											brickManager(std::make_unique<BrickManager>(0)),
											font(mediaCache.getFont(40)),
											brick(nullptr)
{
	GameTex tex = mediaCache.getText("Save Level", font);
	tex->setPosition(0, mediaCache.getScrHeight() - tex->getH());
	menu.push_back(tex);

	tex = mediaCache.getText("Clear Level", font);
	tex->setPosition(mediaCache.getScrWidth() - tex->getW(), mediaCache.getScrHeight() - tex->getH());
	menu.push_back(tex);

	tex = mediaCache.getText("Menu", font);
	tex->setPosition(mediaCache.centreX(tex->getW()), mediaCache.getScrHeight() - tex->getH());
	menu.push_back(tex);

	int x, y;
	SDL_GetMouseState(&x, &y);
	Point2D p{ x,y };
	brick = std::make_unique<Brick>(std::make_unique<BrickInputComponent>(),
									std::make_unique<BrickGraphicsComponent>(),
									p,
									brickColour);
}

LevelEditor::~LevelEditor()
{

}

void LevelEditor::enter(Engine* )
{

}

void LevelEditor::handleEvents(SDL_Event& e, Engine* engine)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
	else if(e.type == SDL_MOUSEWHEEL)
	{
		mouseWheelScrolled(e);
	}
}


void LevelEditor::update(Engine* )
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	
	if (x < 0)
		x = 0;
	else if (x + brick->getWidth() > mediaCache.getScrWidth())
		x = mediaCache.getScrWidth() - brick->getWidth();
	else if (y < 0)
		y = 0;
	else if (y + brick->getHeight() > mediaCache.getScrHeight())
		y = mediaCache.getScrHeight() - brick->getHeight();

	brick->setPosition({ x,y });

	brickManager->update();
}

void LevelEditor::render(const double dTime)
{
	for (const auto& m : menu)
	{
		mediaCache.render(m, m->getPosition());
	}

	brickManager->render(mediaCache, dTime);

	int x, y;
	SDL_GetMouseState(&x, &y);
	bool menuOverlap = false;
	for (const auto& m : menu)
	{
		if (CollisionEngine::haveCollided(m->getBox(), x, y))
		{
			menuOverlap = true;
		}
	}
	if (!menuOverlap)
	{
		brick->render(mediaCache, dTime);
	}
}

void LevelEditor::exit(Engine* )
{

}

void LevelEditor::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (CollisionEngine::haveCollided(menu[0]->getBox(), x, y))
		{

		}
		else if (CollisionEngine::haveCollided(menu[1]->getBox(), x, y))
		{
			brickManager->clear();
		}
		else if (CollisionEngine::haveCollided(menu[2]->getBox(), x, y))
		{
			engine->changeState(std::make_unique<Title>(mediaCache));
		}
		else
		{
			Point2D p{ x,y };
			brickManager->add(std::make_unique<Brick>(std::make_unique<BrickInputComponent>(),
								std::make_unique<BrickGraphicsComponent>(),
								p,
								brickColour));
		}
	}
	//right click on a brick to remove it
	else if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(3)) 
	{
		for (auto& b : brickManager->getBricks())
		{
			if (CollisionEngine::haveCollided(b->getBox(), x, y))
			{
				b->hitByBall();
			}
		}
	}
}

//use the mouse wheel to change the colour of the brick
void LevelEditor::mouseWheelScrolled(SDL_Event& e)
{
	//scroll up
	if (e.wheel.y > 0) 
	{
		++brickColour;
	}
	//scroll down
	else if (e.wheel.y < 0) 
	{
		--brickColour;
	}

	brick->changeColour(brickColour);
}
