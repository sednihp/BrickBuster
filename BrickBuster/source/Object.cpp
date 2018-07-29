#include "Object.h"

Object::Object(std::unique_ptr<InputComponent> ic, 
				std::unique_ptr<GraphicsComponent> gc) : position(0, 0),
														direction(0, 0),
														input(std::move(ic)),
														graphics(std::move(gc))
{
}

Object::~Object()
{

}
