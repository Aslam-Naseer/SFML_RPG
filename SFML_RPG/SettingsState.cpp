#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initBackground()
{
	if (!bgTexture.loadFromFile("Resources/Backgrounds/bg1.png")) {
		std::cerr << "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE" << std::endl;
	}

	background.setSize({ static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y) });
	background.setTexture(&bgTexture);
}

void SettingsState::initKeybinds()
{
}

void SettingsState::initText()
{
	optionsText.setCharacterSize(32);
	optionsText.setFillColor(sf::Color(255, 255, 255, 200));
	optionsText.setPosition({ 400.f, 470.f });

	optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n "
	);
}

void SettingsState::initGui()
{
	buttons["BACK"] = new gui::Button(
		1300.f, 870.f, 150.f, 70.f,
		"Back", font, 36,
		sf::Color(150, 150, 150, 255), sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);

	buttons["APPLY"] = new gui::Button(
		1450.f, 870.f, 150.f, 70.f,
		"Apply", font, 36,
		sf::Color(150, 150, 150, 255), sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);

	dropDownLists["RESOLUTION"] = new gui::DropDownList(700.f, 470.f, 200.f, 50.f, 24, font,
		std::vector<std::string>{ "1920x1080", "1600x900", "1280x720", "1024x576" });
}	

SettingsState::SettingsState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states, sf::Font& font) :
	State(window, supportedKeys, states), font(font), optionsText(font)
{
	initBackground();
	initKeybinds();
	initGui();
	initText();
}

SettingsState::~SettingsState()
{
	for (auto& it : buttons)
	{
		delete it.second;
	}

	for (auto& it : dropDownLists)
	{
		delete it.second;
	}
}

void SettingsState::updateGui(const float& dt)
{
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}

	for (auto& it : dropDownLists)
	{
		it.second->update(mousePosView, dt);
	}

	if (buttons["BACK"]->isPressed())
	{
		endState();
	}

	// Test
	if (buttons["APPLY"]->isPressed())
	{
		short unsigned id = dropDownLists["RESOLUTION"]->getActiveId();
		if (id > 3)
		{
			std::cout << "ERROR id: " << id <<"\n";
			return;
		}

		unsigned int modes_array[4][2] = { {1920, 1080} ,{1600, 900},{1280, 720},{1024, 576} };
		window->create(sf::VideoMode({ modes_array[id][0], modes_array[id][1]}), "Test");
	}

}

void SettingsState::updateInput(const float& dt)
{
}

void SettingsState::update(const float& dt)
{
	/*player.update(dt);
	checkForQuit();*/

	updateMousePositions();
	updateGui(dt);
	updateInput(dt);
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	window->draw(background);
	window->draw(optionsText);

	for (auto& it : buttons)
	{
		it.second->render(*target);
	}

	for (auto& it : dropDownLists)
	{
		it.second->render(*target);
	}

	// DEBUG: REMOVE LATER
	sf::Text mouseText(font, "", 15);
	mouseText.setPosition({ mousePosView.x, mousePosView.y - 20 });
	std::stringstream st;
	st << mousePosView.x << ' ' << mousePosView.y;
	mouseText.setString(st.str());

	target->draw(mouseText);
}
