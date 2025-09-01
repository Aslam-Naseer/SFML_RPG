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

	std::vector<std::string> modes_str;
	for (auto& i : gfxSettings.videoModes)
	{
		modes_str.push_back(std::to_string(i.size.x) + 'x' + std::to_string(i.size.y));
	}

	dropDownLists["RESOLUTION"] = new gui::DropDownList(700.f, 470.f, 200.f, 50.f, 24, font, modes_str);
}	

SettingsState::SettingsState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states, sf::Font& font) :
	State(window, supportedKeys, states), gfxSettings(gfxSettings), font(font), optionsText(font)
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
		if (id >= gfxSettings.videoModes.size())
		{
			std::cout << "ERROR id: " << id <<"\n";
			return;
		}

		unsigned int modes_array[4][2] = { {1920, 1080} ,{1600, 900},{1280, 720},{1024, 576} };
		window->create(sf::VideoMode({ gfxSettings.videoModes[id].size.x, gfxSettings.videoModes[id].size.y }), gfxSettings.title);
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
