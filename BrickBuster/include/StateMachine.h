#pragma once
#include "State.h"
#include <memory>
class Engine;

class StateMachine
{
	private:
		Engine* owner;
		std::unique_ptr<State> currentState;

	public:
		StateMachine(Engine* engine, std::unique_ptr<State> s);
		~StateMachine();

		const std::unique_ptr<State>& getCurrentState() const { return currentState; }
		void changeState(std::unique_ptr<State> newState);
};