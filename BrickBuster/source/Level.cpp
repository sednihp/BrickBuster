#include "Level.h"
#include "CollisionEngine.h"
#include <string>
#include "Engine.h"
#include "Title.h"
#include <memory>

Level::Level(MediaCache& mc) : State(mc),
								bat(std::make_unique<Bat>(mediaCache.getScrWidth(), mediaCache.getScrHeight())),
								ball(std::make_unique<Ball>("files/images/ball/ball.bmp", mediaCache.getScrWidth(), static_cast<int>(bat->getPosition().y)))
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

	checkIfBallMoving();
	ball->move(mediaCache.getScrWidth(), mediaCache.getScrHeight(), bat->getBox(), blocks, dTime);

	removeDestroyedBlocks();
}

void Level::removeDestroyedBlocks()
{
	auto b = blocks.begin();
	while (b != blocks.end())
	{
		if (!(*b)->isAlive())
		{
			b = blocks.erase(b);
		}
		else
		{
			++b;
		}
	}
}

void Level::render()
{
	mediaCache.drawRectangle(bat->getBox(), bat->getColor());
	for (const auto& block : blocks)
	{
		mediaCache.drawRectangle(block->getBox(), block->getColor());
	}
	mediaCache.renderTexture(mediaCache.getImage(ball->getImage()), static_cast<int>(ball->getPosition().x), static_cast<int>(ball->getPosition().y));
}

void Level::exit(Engine* )
{

}

// ===============
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

void Level::checkIfBallMoving()
{
	if (!ball->isMoving() && bat->getDirection().x != 0)
	{
		ball->startMoving(bat->getDirection().x, -1);
	}
}