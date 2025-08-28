#include "State.h"


State::State(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states) :
	supportedKeys(supportedKeys), window(window), states(states), quit(false), paused(false)

{
	keyTime = 0.f;
	maxKeyTime = 10.f;
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
