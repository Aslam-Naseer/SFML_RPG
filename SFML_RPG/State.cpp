#include "State.h"


State::State(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states) :
	supportedKeys(supportedKeys), window(window), states(states), quit(false)

{
}

State::~State()
{
}

void State::endState()
{
		quit = true;
}

const bool& State::getQuit() const
{
	return quit;
}

void State::updateMousePositions()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}
