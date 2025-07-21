#include "State.h"

State::State(sf::RenderWindow *window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys):
	supportedKeys(supportedKeys)
{
	this->window = window;
	quit = false;
}

State::~State()
{
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
	{
		quit = true;
	}
}

const bool& State::getQuit() const
{
	return quit;
}
