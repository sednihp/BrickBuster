#pragma once

#include "MediaCache.h"
#include "StateMachine.h"
#include <memory>

class Engine
{
	private: 
		bool running = true;
		const double fps = 60;
		const double frameLength = 1000.0 / fps;
		double previous, lag;
		MediaCache mediaCache;
		std::unique_ptr<StateMachine> stateMachine;

		void handleEvents();
		void update();
		void render();

	public:
		Engine();
		~Engine();

		void run();
		void stopRunning() { running = false; }
		void changeState(std::unique_ptr<State> newState);
};