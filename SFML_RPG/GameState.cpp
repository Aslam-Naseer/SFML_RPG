#include "GameState.h"

GameState::GameState(sf::RenderWindow* window):
	State(window)
{
}

GameState::~GameState()
{
}

void GameState::endState()
{
	std::cout << "Ending GameState" << std::endl;
}

void GameState::update(const float& dt)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
	{
		std::cout << "A key pressed!" << std::endl;
	}

	checkForQuit();
}

void GameState::render(sf::RenderTarget* target)
{
}
