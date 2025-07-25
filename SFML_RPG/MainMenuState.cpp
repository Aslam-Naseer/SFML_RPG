#include "MainMenuState.h"

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	std::string key, key_code;
	while (ifs >> key >> key_code)
		keybinds[key] = supportedKeys.at(key_code);


}

void MainMenuState::initFonts()
{
	if (!font.openFromFile("Fonts/Dosis-Light.ttf")) {
		throw std::runtime_error("ERROR::GAME::FONT_NOT_AVAILABLE");
	}
}

MainMenuState::MainMenuState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys) :
	State(window, supportedKeys)
{
	background.setFillColor(sf::Color::Cyan);
	background.setSize({ window->getSize().x - 300.f, window->getSize().y - 200.f });
	background.setPosition({ 150, 100 });

	initKeybinds();
	initFonts();

	button = new Button(200.f, 200.f, 100.f, 50.f, "Play", font,
		sf::Color(70,70,70,200), sf::Color(200,200,200,255), sf::Color(20,20,20,20));
}

MainMenuState::~MainMenuState()
{
	delete button;
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
	button->update(mousePosView);
	updateInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	window->draw(background);
	button->render(target);
}
