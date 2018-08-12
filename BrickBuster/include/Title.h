#pragma once
#include "State.h"
#include <vector>

class Title : public State
{
	private:
		TTF_Font* font;
		TTF_Font* menuFont;
		GameTex titleTex;
		std::vector<GameTex> menu;

		void generateTextures();
		void mouseClicked(SDL_Event& e, Engine* engine);
		
	public:
		Title(MediaCache &mc);
		~Title();

		virtual void enter(Engine* engine);
		virtual void handleEvents(SDL_Event& e, Engine* engine);
		virtual void update(Engine* engine);
		virtual void render(const double dTime);
		virtual void exit(Engine* engine);
};
