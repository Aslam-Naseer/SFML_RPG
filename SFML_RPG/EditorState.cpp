#include "stdafx.h"
#include "EditorState.h"

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	std::string key, key_code;
	while (ifs >> key >> key_code)
		keybinds[key] = stateData.supportedKeys->at(key_code);

	ifs.close();
}

void EditorState::initTextures()
{
	if (!textures["PLAYER_SHEET"].loadFromFile("Resources/Sprites/Player/PLAYER_SHEET.png"))
	{
		std::cout << "ERROR::GAMESTATE::INITTEXTURES::Could not load texture PLAYER_SHEET" << std::endl;
	}
}

void EditorState::initGui()
{
	selectorRect.setSize({ gridSize, gridSize });
	selectorRect.setFillColor(sf::Color::Transparent);
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::Green);
}

EditorState::EditorState(StateData& state_data, sf::Font& font) :
	State(state_data), pmenu(*window, font), tileMap(state_data.gridSize), gridSize(state_data.gridSize)
{
	initKeybinds();
	initTextures();
	initGui();
}

EditorState::~EditorState()
{
}

void EditorState::updatePauseMenuButtons()
{
	if (pmenu.isButtonPressed("QUIT"))
		endState();
}

void EditorState::updateGui()
{
	selectorRect.setPosition({
		mousePosGrid.x * gridSize,
		mousePosGrid.y * gridSize,
		});
}

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(keybinds["CLOSE"]) && getKeyTime())
	{
		if (!paused)
			pauseState();
		else
			unpauseState();
	}
}

void EditorState::update(const float& dt)
{
	updateMousePositions();
	updateKeyTime(dt);
	updateInput(dt);

	if (!paused)
	{
		updateGui();
	}

	else
	{
		pmenu.update(mousePosView);
		updatePauseMenuButtons();
	}

}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	tileMap.render(*target);
	target->draw(selectorRect);

	if (paused)
	{
		pmenu.render(*target);
	}

}
