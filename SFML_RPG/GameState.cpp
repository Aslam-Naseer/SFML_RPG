#include "GameState.h"

void GameState::initKeybinds()
{
	keybinds["MOVE_LEFT"] = supportedKeys.at("A");
	keybinds["MOVE_DOWN"] = supportedKeys.at("S");
	keybinds["MOVE_UP"] = supportedKeys.at("W");
	keybinds["MOVE_RIGHT"] = supportedKeys.at("D");
}

GameState::GameState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys):
	State(window, supportedKeys)
{
	initKeybinds();
}

GameState::~GameState()
{
}

void GameState::endState()
{
	std::cout << "Ending GameState" << std::endl;
}

void GameState::updateInput(const float& dt)
{
	checkForQuit();

	if(sf::Keyboard::isKeyPressed(keybinds["MOVE_LEFT"]))
	{
		player.move(dt, -1, 0);
	}
	if (sf::Keyboard::isKeyPressed(keybinds["MOVE_RIGHT"]))
	{
		player.move(dt, 1, 0);
	}
	if (sf::Keyboard::isKeyPressed(keybinds["MOVE_UP"]))
			{
		player.move(dt, 0, -1);
	}
	if (sf::Keyboard::isKeyPressed(keybinds["MOVE_DOWN"]))
	{
		player.move(dt, 0, 1);
	}
}

void GameState::update(const float& dt)
{
	/*player.update(dt);
	checkForQuit();*/

	updateInput(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	player.render(target);
}
