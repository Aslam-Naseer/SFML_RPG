#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initKeybinds()
{
}

void MainMenuState::initFonts()
{
	if (!fonts["DEFAULT"].openFromFile("Fonts/Dosis-Light.ttf")) {
		throw std::runtime_error("ERROR::GAME::FONT_DOSIS_NOT_AVAILABLE");
	}

	if (!fonts["TEXTTAG"].openFromFile("Fonts/PixellettersFull.ttf")) {
		throw std::runtime_error("ERROR::GAME::FONT_NOT_AVAILABLE");
	}
}

void MainMenuState::initGui()
{
	// Backgrond

	if (!bgTexture.loadFromFile("Resources/Backgrounds/bg2.png")) {
		std::cerr << "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE" << std::endl;
	}

	background.setSize({ static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y) });
	background.setTexture(&bgTexture);


	// Buttons

	buttons["GAME_STATE"] = new gui::Button(
		utils::p2pX(12.f), utils::p2pY(30.7f), utils::p2pX(14.f), utils::p2pY(9.3f),
		"New Game", fonts["DEFAULT"], utils::calcCharSize(2),
		sf::Color(150, 150, 150, 255), sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);

	buttons["SETTINGS_STATE"] = new gui::Button(
		utils::p2pX(12.f), utils::p2pY(40.9f), utils::p2pX(14.f), utils::p2pY(9.3f),
		"Settings", fonts["DEFAULT"], utils::calcCharSize(2),
		sf::Color(150, 150, 150, 255), sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);

	buttons["EDITOR_STATE"] = new gui::Button(
		utils::p2pX(12.f), utils::p2pY(51.1f), utils::p2pX(14.f), utils::p2pY(9.3f),
		"Editor", fonts["DEFAULT"], utils::calcCharSize(2),
		sf::Color(150, 150, 150, 255), sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);

	buttons["EXIT"] = new gui::Button(
		utils::p2pX(12.f), utils::p2pY(68.7f), utils::p2pX(14.f), utils::p2pY(9.3f),
		"Exit", fonts["DEFAULT"], utils::calcCharSize(2),
		sf::Color(150, 150, 150, 255), sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);

}

void MainMenuState::resetGui()
{
	for (auto& it : buttons)
	{
		delete it.second;
	}

	initGui();
}

MainMenuState::MainMenuState(StateData& state_data) :
	State(state_data)
{
	initKeybinds();
	initFonts();
	initGui();
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
		it.second->update(mousePosWindow);
	}

	if (buttons["GAME_STATE"]->isPressed())
	{
		states.push(new GameState(stateData, fonts));
	}

	if(buttons["SETTINGS_STATE"]->isPressed())
	{
		states.push(new SettingsState(stateData, fonts["DEFAULT"]));
	}

	if (buttons["EDITOR_STATE"]->isPressed())
	{
		states.push(new EditorState(stateData, fonts["DEFAULT"]));
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

}
