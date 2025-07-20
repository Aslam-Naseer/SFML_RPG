#include "GameState.h"

GameState::GameState(sf::RenderWindow* window):
	State(window)
{
}

GameState::~GameState()
{
}

void GameState::update(const float& dt)
{
	std::cout << "GameState Update: " << dt << std::endl; 
}

void GameState::render(sf::RenderTarget* target)
{
}
