#pragma once

#include "MediaCache.h"
#include "StateMachine.h"
#include <memory>

class Engine
{
	private: 
		bool running;
		double previous, lag;
		const double fps = 60;
		const double frameLength = 1000.0 / fps;
		MediaCache mediaCache;
		std::unique_ptr<StateMachine> stateMachine;
		unsigned int randomNumber;

		void handleEvents();
		void update();
		void render();

	public:
		Engine();
		~Engine();

		void run();
		void stopRunning() { running = false; }
		void changeState(std::shared_ptr<State> newState);
};