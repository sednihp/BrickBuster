#include "GraphicsComponent.h"
#include "Object.h"

#include <iostream>

void BatGraphicsComponent::render(Object& obj, MediaCache& mc)
{
	mc.drawRectangle(obj.getBox(), obj.getColor());
}

void BallGraphicsComponent::render(Object& obj, MediaCache& mc)
{
	mc.renderTexture(mc.getImage(obj.getImage()), obj.getPosition().x, obj.getPosition().y);
}

void BlockGraphicsComponent::render(Object& obj, MediaCache& mc)
{
	mc.drawRectangle(obj.getBox(), obj.getColor());
}