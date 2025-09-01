#include "stdafx.h"
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
}

void MainMenuState::initFonts()
{
	if (!font.openFromFile("Fonts/Dosis-Light.ttf")) {
		throw std::runtime_error("ERROR::GAME::FONT_NOT_AVAILABLE");
	}
}

void MainMenuState::initButtons()
{

	buttons["GAME_STATE"] = new gui::Button(
		230.f, 440.f, 270.f, 100.f,
		"New Game", font, 50,
		sf::Color(70, 70, 70, 255), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);

	buttons["SETTINGS_STATE"] = new gui::Button(
		230.f, 550.f, 270.f, 100.f,
		"Settings", font, 50,
		sf::Color(70, 70, 70, 255), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);

	buttons["EDITOR_STATE"] = new gui::Button(
		230.f, 660.f, 270.f, 100.f,
		"Editor", font, 50,
		sf::Color(70, 70, 70, 255), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);

	buttons["EXIT"] = new gui::Button(
		230.f, 850.f, 270.f, 100.f,
		"Exit", font, 50,
		sf::Color(70, 70, 70, 255), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);
}

MainMenuState::MainMenuState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states) :
	State(window, supportedKeys, states), gfxSettings(gfxSettings)
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
		states.push(new GameState(window, supportedKeys, states, font));
	}

	if(buttons["SETTINGS_STATE"]->isPressed())
	{
		states.push(new SettingsState(window, gfxSettings, supportedKeys, states, font));
	}

	if (buttons["EDITOR_STATE"]->isPressed())
	{
		states.push(new EditorState(window, supportedKeys, states));
	}

	if (buttons["EXIT"]->isPressed())
	{
		endState();
	}
}

void MainMenuState::updateInput(const float& dt)
{
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
		it.second->render(*target);
	}

	// DEBUG: REMOVE LATER
	sf::Text mouseText(font,"",15);
	mouseText.setPosition({mousePosView.x, mousePosView.y - 20});
	std::stringstream st;
	st << mousePosView.x << ' ' << mousePosView.y;
	mouseText.setString(st.str());

	target->draw(mouseText);
}
