#include "Object.h"

Object::Object(const std::string& img) : image(img), 
										position(0, 0),
										direction(0, 0)
{

}

Object::Object() : Object("")
{

}

Object::~Object()
{

}
