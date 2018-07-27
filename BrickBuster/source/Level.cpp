#include "Level.h"
#include "CollisionEngine.h"
#include <string>
#include "Engine.h"
#include "Title.h"
#include <memory>

Level::Level(MediaCache& mc) : State(mc),
								bat(std::make_unique<Bat>(mediaCache.getScrWidth(), mediaCache.getScrHeight()))
{
	Point2D p{ 10,100 };
	for (int i = 0; i < 6; i++)
	{
		blocks.push_back(std::make_unique<Block>(p, BrickBuster::BlockColor::RED));
		p.x += 100;
	}
	const int margin = 2 * blocks[0]->getHeight();
	p.x = 10;
	p.y += margin;
	for (int i = 0; i < 6; i++)
	{
		blocks.push_back(std::make_unique<Block>(p, BrickBuster::BlockColor::ORANGE));
		p.x += 100;
	}
	p.x = 10;
	p.y += margin;
	for (int i = 0; i < 6; i++)
	{
		blocks.push_back(std::make_unique<Block>(p, BrickBuster::BlockColor::YELLOW));
		p.x += 100;
	}
	p.x = 10;
	p.y += margin;
	for (int i = 0; i < 6; i++)
	{
		blocks.push_back(std::make_unique<Block>(p, BrickBuster::BlockColor::GREEN));
		p.x += 100;
	}
	p.x = 10;
	p.y += margin;
	for (int i = 0; i < 6; i++)
	{
		blocks.push_back(std::make_unique<Block>(p, BrickBuster::BlockColor::BLUE));
		p.x += 100;
	}
	p.x = 10;
	p.y += margin;
	for (int i = 0; i < 6; i++)
	{
		blocks.push_back(std::make_unique<Block>(p, BrickBuster::BlockColor::PURPLE));
		p.x += 100;
	}
}

Level::~Level()
{

}

void Level::enter(Engine* )
{

}

void Level::handleEvents(SDL_Event &e, Engine* engine)
{
	keyPressed(e, engine);
}

void Level::update(const double dTime, Engine* )
{
	bat->move(mediaCache.getScrWidth(), dTime);
}

void Level::render()
{
	mediaCache.drawRectangle(bat->getBox(), bat->getColor());
	for (const auto& block : blocks)
	{
		mediaCache.drawRectangle(block->getBox(), block->getColor());
	}
}

void Level::exit(Engine* )
{

}

// ===============
// Class Functions
// ===============

void Level::keyPressed(SDL_Event &e, Engine*)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_LEFT:
			case SDLK_a:
				bat->setDirection({ -1,0 });
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				bat->setDirection({ 1,0 });
				break;
		}
	}
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_LEFT:
			case SDLK_a:
				bat->setDirection({ 0,0 });
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				bat->setDirection({ 0,0 });
				break;
		}
	}
}