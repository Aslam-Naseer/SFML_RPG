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
	player.update(dt);
	checkForQuit();
}

void GameState::render(sf::RenderTarget* target)
{
	player.render(window);
}
