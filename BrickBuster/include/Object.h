#pragma once
#include "Vectors.h"
#include "InputComponent.h"
#include "GraphicsComponent.h"
#include <string>
#include "SDL.h"
#include <memory>
#include <iostream>

class Object
{
	protected:
		Point2D position;
		Vector2D direction;
		std::string image = "";
		SDL_Rect box = { 0,0,1,1 };
		SDL_Color color = { 0,0,0 };
		std::unique_ptr<InputComponent> input;
		std::unique_ptr<GraphicsComponent> graphics;

	public:
		Object(std::unique_ptr<InputComponent> ic, 
				std::unique_ptr<GraphicsComponent> gc);
		~Object();

		virtual const Point2D getPosition() { return position; }
		virtual const SDL_Rect& getBox() { return box; }
		const Vector2D& getDirection() const { return direction; }
		const std::string& getImage() const { return image; }
		const SDL_Color& getColor() const { return color; }

		void setDirection(const Vector2D& dir) { direction = dir; }

		void handleEvents(SDL_Event &e) { input->handleEvents(*this, e); }
		void render(MediaCache& mc) { graphics->render(*this, mc); }
};