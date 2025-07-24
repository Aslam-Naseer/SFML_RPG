#include "MainMenuState.h"

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	std::string key, key_code;
	while (ifs >> key >> key_code)
		keybinds[key] = supportedKeys.at(key_code);


}

MainMenuState::MainMenuState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys) :
	State(window, supportedKeys)
{
	background.setFillColor(sf::Color::Cyan);
	background.setSize({ window->getSize().x - 300.f, window->getSize().y - 200.f });
	background.setPosition({ 150, 100 });

	initKeybinds();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::endState()
{
	std::cout << "Ending MainMenuState" << std::endl;
}

void MainMenuState::updateInput(const float& dt)
{
	checkForQuit();
}

void MainMenuState::update(const float& dt)
{
	/*player.update(dt);
	checkForQuit();*/

	updateMousePositions();
	updateInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	window->draw(background);
}
