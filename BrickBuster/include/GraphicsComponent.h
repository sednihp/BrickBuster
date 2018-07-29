#pragma once
#include "MediaCache.h"
class Object;

class GraphicsComponent {
public:
	virtual ~GraphicsComponent() {}
	virtual void render(Object& obj, MediaCache& mc) = 0;
};

class BatGraphicsComponent : public GraphicsComponent {
public:
	virtual void render(Object& obj, MediaCache& mc);
};

class BallGraphicsComponent : public GraphicsComponent {
public:
	virtual void render(Object& obj, MediaCache& mc);
};

class BlockGraphicsComponent : public GraphicsComponent {
public:
	virtual void render(Object& obj, MediaCache& mc);
};