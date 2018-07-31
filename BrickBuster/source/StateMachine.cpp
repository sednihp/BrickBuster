#include "StateMachine.h"
#include "Engine.h"

StateMachine::StateMachine(Engine* owner, std::unique_ptr<State> s) : owner(owner),
																	currentState(std::move(s))
{
}

StateMachine::~StateMachine()
{
}

//if we try to change to the same state, return immediately
//otherwise exit out of the current state, assign newState to currentState and enter the new state
void StateMachine::changeState(std::unique_ptr<State> newState)
{
	if(typeid(*currentState) == typeid(*newState))
	{
		return;
	}

	currentState->exit(owner);

	currentState = std::move(newState);

	currentState->enter(owner);
}