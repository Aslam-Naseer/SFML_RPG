#include "stdafx.h"
#include "State.h"

State::State(StateData& state_data) :
	stateData(state_data), states(*state_data.states)
{
	keyTime = 0.f;
	maxKeyTime = 10.f;
	window = stateData.window;
}

State::~State()
{
}

void State::endState()
{
		quit = true;
}

void State::pauseState()
{
	paused = true;
}

void State::unpauseState()
{
	paused = false;
}

const bool& State::getQuit() const
{
	return quit;
}

const bool State::getKeyTime()
{
	if(keyTime >= maxKeyTime)
	{
		keyTime = 0.f;
		return true;
	}

	return false;
}

void State::updateMousePositions()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void State::updateKeyTime(const float& dt)
{
	if (keyTime < maxKeyTime)
		keyTime += 100.f * dt;
}
