#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initKeybinds()
{
}

void SettingsState::initGui()
{
	// Background

	if (!bgTexture.loadFromFile("Resources/Backgrounds/bg1.png")) {
		std::cerr << "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE" << std::endl;
	}

	background.setSize({ static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y) });
	background.setTexture(&bgTexture);


	// Buttons
	buttons["BACK"] = new gui::Button(
		utils::p2pX(67.7f), utils::p2pY(80.5f), utils::p2pX(7.8f), utils::p2pY(6.5f),
		"Back", font, utils::calcCharSize(1.4f),
		sf::Color(150, 150, 150, 255), sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);

	buttons["APPLY"] = new gui::Button(
		utils::p2pX(75.5f), utils::p2pY(80.5f), utils::p2pX(7.8f), utils::p2pY(6.5f),
		"Apply", font, utils::calcCharSize(1.4f),
		sf::Color(150, 150, 150, 255), sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);


	// Dropdown List

	int id = 0;
	std::vector<std::string> modes_str;
	for (auto& i : gfxSettings.videoModes)
	{
		modes_str.push_back(std::to_string(i.size.x) + 'x' + std::to_string(i.size.y));
		if (gfxSettings.resolution == i) id = static_cast<int>(modes_str.size() - 1);
	}

	dropDownLists["RESOLUTION"] = new gui::DropDownList(utils::p2pX(36.4f), utils::p2pY(43.5f), utils::p2pX(10.4f), utils::p2pY(4.6f), utils::calcCharSize(1), font, modes_str, id);


	// Text

	optionsText.setCharacterSize(utils::calcCharSize(1.3f));
	optionsText.setFillColor(sf::Color(255, 255, 255, 200));
	optionsText.setPosition({ utils::p2pX(20.8f), utils::p2pY(43.5f) });

	optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n "
	);
}	

void SettingsState::resetGui()
{
	for(auto& it : buttons)
	{
		delete it.second;
	}

	for(auto& it : dropDownLists)
	{
		delete it.second;
	}

	initGui();
}

SettingsState::SettingsState(StateData& state_data, sf::Font& font) :
	State(state_data), gfxSettings(*state_data.gfxSettings), font(font), optionsText(font)
{
	initKeybinds();
	initGui();
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
		it.second->update(mousePosWindow);
	}

	for (auto& it : dropDownLists)
	{
		it.second->update(mousePosWindow, dt);
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

		gfxSettings.updateResolution(window, id);
		resetGui();
	}

}

void SettingsState::updateInput(const float& dt)
{
}

void SettingsState::update(const float& dt)
{
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

}
