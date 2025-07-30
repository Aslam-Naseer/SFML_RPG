#include "MainMenuState.h"

void MainMenuState::initBackground()
{
	if(!bgTexture.loadFromFile("Resources/Backgrounds/bg1.png")) {
		std::cerr << "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE" << std::endl;
	}
	
	background.setSize({ static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y) });
	background.setTexture(&bgTexture);
}

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

void MainMenuState::initButtons()
{

	buttons["GAME_STATE"] = new Button(230.f, 510.f, 100.f, 50.f, "New Game", font,
		sf::Color(70, 70, 70, 200), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 200));


	buttons["EXIT"] = new Button(230.f, 610.f, 100.f, 50.f, "Exit", font,
		sf::Color(70, 70, 70, 200), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states) :
	State(window, supportedKeys, states)
{

	initBackground();
	initKeybinds();
	initFonts();
	initButtons();

}

MainMenuState::~MainMenuState()
{
	for(auto& it : buttons)
	{
		delete it.second;
	}
}

void MainMenuState::updateButtons()
{
	for(auto& it : buttons)
	{
		it.second->update(mousePosView);
	}

	if (buttons["GAME_STATE"]->isPressed())
	{
		states.push(new GameState(window, supportedKeys, states));
	}

	if (buttons["EXIT"]->isPressed())
	{
		std::cout << "Exit Button Pressed" << std::endl;
		quit = true;
	}
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
	updateButtons();
	updateInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	window->draw(background);
	
	for(auto& it: buttons)
	{
		it.second->render(target);
	}

	// DEBUG: REMOVE LATER
	sf::Text mouseText(font,"",15);
	mouseText.setPosition({mousePosView.x, mousePosView.y - 20});
	std::stringstream st;
	st << mousePosView.x << ' ' << mousePosView.y;
	mouseText.setString(st.str());

	target->draw(mouseText);
}
