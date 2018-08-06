#include "GraphicsComponent.h"
#include "GameObject.h"
#include <iostream>

void BatGraphicsComponent::render(GameObject& obj, MediaCache& mc)
{
	mc.render(obj.getBox(), obj.getColor());
}

void BallGraphicsComponent::render(GameObject& obj, MediaCache& mc)
{
	mc.render(mc.getImage(obj.getImage()), obj.getPosition());
}

void BrickGraphicsComponent::render(GameObject& obj, MediaCache& mc)
{
	mc.render(obj.getBox(), obj.getColor());
}

void PowerUpGraphicsComponent::render(GameObject& obj, MediaCache& mc)
{
	mc.render(mc.getImage(obj.getImage()), obj.getPosition());
}

void BrickScoreGraphicsComponent::render(GameObject& obj, MediaCache& mc)
{
	TTF_Font* font = mc.getFont(30);
	mc.render(mc.getText(obj.getImage(), font), obj.getPosition());
}