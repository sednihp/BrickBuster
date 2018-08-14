#include "LevelEditor.h"
#include "CollisionEngine.h"
#include "Engine.h"
#include "LevelSelector.h"
#include <fstream>
#include "GameException.h"

LevelEditor::LevelEditor(MediaCache& mc, int levelNum) : State(mc), level(levelNum),
														brickManager(std::make_unique<BrickManager>(levelNum)),
														font(mediaCache.getFont(40))
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

	tex = mediaCache.getText("Level " + std::to_string(levelNum) + " Editor", font);
	tex->setPosition(mediaCache.centreX(tex->getW()), 5);
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
	brick->setPosition(getBrickPosition());

	brickManager->update(mediaCache.getScrWidth(), mediaCache.getScrHeight());
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
			saveLevel();
		}
		else if (CollisionEngine::haveCollided(menu[1]->getBox(), x, y))
		{
			brickManager->clear();
		}
		else if (CollisionEngine::haveCollided(menu[2]->getBox(), x, y))
		{
			engine->changeState(std::make_unique<LevelSelector>(LevelSelectorState::EDITOR, mediaCache));
		}
		else
		{
			brickManager->add(std::make_unique<Brick>(std::make_unique<BrickInputComponent>(),
								std::make_unique<BrickGraphicsComponent>(),
								getBrickPosition(),
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
				b->eraseBrick();
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

const Point2D LevelEditor::getBrickPosition()
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


	//the below implements snap-to-grid to make designing columsn and rows easier
	int xDiff = x % 100;
	if (xDiff < 10)
	{
		x -= xDiff;
	}
	else if (xDiff > 90)
	{
		x += (100 - xDiff);
	}

	int yDiff = y % 40;
	if (yDiff < 10)
	{
		y -= yDiff;
	}
	else if (yDiff > 30)
	{
		y += (40 - yDiff);
	}

	return { x,y };
}

void LevelEditor::saveLevel()
{
	std::ofstream outputFile("files/levels/" +std::to_string(level) +".lvl");

	if (!outputFile)
	{
		std::string msg = "Output file not opened";
		GameException e(msg);
		throw e;
	}

	//ensure there is no newline char on the last line 
	//that causes issues with destroying the last brick when the level is loaded to play
	for (size_t i = 0; i < brickManager->getBricks().size(); i++)
	{
		const std::unique_ptr<Brick>& b = brickManager->getBricks()[i];
		if (i == brickManager->getBricks().size() - 1)
		{
			outputFile << b->getBrickColour() << " " << b->getPosition().x << " " << b->getPosition().y;
		}
		else
		{
			outputFile << b->getBrickColour() << " " << b->getPosition().x << " " << b->getPosition().y << "\n";
		}
	}

	outputFile.close();
}