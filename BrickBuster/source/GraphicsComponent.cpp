#include "GraphicsComponent.h"
#include "GameObject.h"
#include <iostream>

void BatGraphicsComponent::render(GameObject& obj, MediaCache& mc)
{
	mc.drawRectangle(obj.getBox(), obj.getColor());
}

void BallGraphicsComponent::render(GameObject& obj, MediaCache& mc)
{
	mc.renderTexture(mc.getImage(obj.getImage()), obj.getPosition());
}

void BrickGraphicsComponent::render(GameObject& obj, MediaCache& mc)
{
	mc.drawRectangle(obj.getBox(), obj.getColor());
}

void PowerUpGraphicsComponent::render(GameObject& obj, MediaCache& mc)
{
	mc.renderTexture(mc.getImage(obj.getImage()), obj.getPosition());
}

void BrickScoreGraphicsComponent::render(GameObject& obj, MediaCache& mc)
{
	TTF_Font* font = mc.getFont(20);
	mc.renderTexture(mc.getText(obj.getImage(), font), obj.getPosition());
}