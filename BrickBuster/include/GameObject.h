#pragma once
#include "Vectors.h"
#include "InputComponent.h"
#include "GraphicsComponent.h"
#include <string>
#include "SDL.h"
#include <memory>
#include <iostream>

class GameObject
{
	protected:
		Point2D position = { 0,0 };
		Vector2D direction = { 0,0 };
		SDL_Rect box = { 0,0,1,1 };
		SDL_Color color = { 0,0,0 };
		std::string image = "";
		std::unique_ptr<InputComponent> input;
		std::unique_ptr<GraphicsComponent> graphics;

	public:
		GameObject(std::unique_ptr<InputComponent> ic, 
				std::unique_ptr<GraphicsComponent> gc);
		~GameObject();

		virtual const Point2D getPosition() { return position; }
		virtual const SDL_Rect& getBox() { return box; }
		const Vector2D& getDirection() const { return direction; }
		const std::string& getImage() const { return image; }
		const SDL_Color& getColor() const { return color; }

		void setPosition(const Point2D& p) { position = p; }
		void setBox(const SDL_Rect& r) { box = r; }
		void setDirection(const Vector2D& d) { direction = d; }
		void setImage(const std::string i) { image = i; }
		void setColor(const SDL_Color& c) { color = c; }		

		void handleEvents(SDL_Event &e) { input->handleEvents(*this, e); }
		void render(MediaCache& mc) { graphics->render(*this, mc); }
};