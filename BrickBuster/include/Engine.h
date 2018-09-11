#pragma once
#include "MediaCache.h"
#include "StateMachine.h"
#include <memory>
#include <random>

class Engine
{
	private: 
		bool running = true;
		const double fps = 60;
		const double frameLength = 1000.0 / fps;
		double previous, lag;
		MediaCache mediaCache;
		std::unique_ptr<StateMachine> stateMachine;
		Mix_Music* music;

		void handleEvents();
		void update();
		void render(const double dt);

	public:
		Engine();
		~Engine();

		void run();
		void stopRunning() { running = false; }
		void changeState(std::unique_ptr<State> newState);
};