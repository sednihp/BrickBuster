#include "GraphicsComponent.h"
#include "GameObject.h"
#include <iostream>

void BatGraphicsComponent::render(GameObject& obj, const double dTime, MediaCache& mc)
{
	SDL_Rect r = obj.getBox();
	r.x += static_cast<int>(obj.getDirection().x * obj.getSpeed() * dTime);
	mc.render(r, obj.getColor());
}

void BallGraphicsComponent::render(GameObject& obj, const double dTime, MediaCache& mc)
{
	Point2D p = obj.getPosition();
	p.x += obj.getDirection().x * obj.getSpeed() * dTime;
	p.y += obj.getDirection().y * obj.getSpeed() * dTime;
	mc.render(mc.getImage(obj.getImage()), p);
}

void BrickGraphicsComponent::render(GameObject& obj, const double , MediaCache& mc)
{
	mc.render(obj.getBox(), obj.getColor());
}

void PowerUpGraphicsComponent::render(GameObject& obj, const double dTime, MediaCache& mc)
{
	TTF_Font* font = mc.getFont(15);
	Point2D p = obj.getPosition();
	p.y += obj.getDirection().y * obj.getSpeed() * dTime;
	mc.render(mc.getText(obj.getImage(), font), p);
}

void BrickScoreGraphicsComponent::render(GameObject& obj, const double , MediaCache& mc)
{
	TTF_Font* font = mc.getFont(30);
	mc.render(mc.getText(obj.getImage(), font), obj.getPosition());
}