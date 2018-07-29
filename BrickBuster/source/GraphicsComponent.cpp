#include "GraphicsComponent.h"
#include "GameObject.h"

#include <iostream>

void BatGraphicsComponent::render(GameObject& obj, MediaCache& mc)
{
	mc.drawRectangle(obj.getBox(), obj.getColor());
}

void BallGraphicsComponent::render(GameObject& obj, MediaCache& mc)
{
	mc.renderTexture(mc.getImage(obj.getImage()), obj.getPosition().x, obj.getPosition().y);
}

void BlockGraphicsComponent::render(GameObject& obj, MediaCache& mc)
{
	mc.drawRectangle(obj.getBox(), obj.getColor());
}