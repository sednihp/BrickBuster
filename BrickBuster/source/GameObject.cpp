#include "GameObject.h"

GameObject::GameObject(std::unique_ptr<InputComponent> ic, 
						std::unique_ptr<GraphicsComponent> gc) : input(std::move(ic)),
																graphics(std::move(gc))
{
}

GameObject::~GameObject()
{

}
