#pragma once
#include "MediaCache.h"
class GameObject;

class GraphicsComponent {
public:
	virtual ~GraphicsComponent() {}
	virtual void render(GameObject& obj, MediaCache& mc) = 0;
};

class BatGraphicsComponent : public GraphicsComponent {
public:
	virtual void render(GameObject& obj, MediaCache& mc);
};

class BallGraphicsComponent : public GraphicsComponent {
public:
	virtual void render(GameObject& obj, MediaCache& mc);
};

class BrickGraphicsComponent : public GraphicsComponent {
public:
	virtual void render(GameObject& obj, MediaCache& mc);
};