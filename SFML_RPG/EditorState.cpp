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
	textureRect.position.x = 0;
	textureRect.position.y = 0;
	textureRect.size.x = 100;
	textureRect.size.y = 100;
}

void EditorState::initGui()
{
	selectorRect.setSize({ gridSize, gridSize });
	selectorRect.setFillColor(sf::Color(255, 255, 255, 155));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::White);
	
	selectorRect.setTexture(&tileMap.getTileSheet());
	selectorRect.setTextureRect(textureRect);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) && getKeyTime()) {
		
		sf::Vector2i& texturePos = textureRect.position;

		if (texturePos.x == 0 && texturePos.y == 0) {
			texturePos.x = 100;

		} else if (texturePos.x == 100 && texturePos.y == 0) {
			texturePos.x = 0;
			texturePos.y = 100;

		} else if (texturePos.x == 0 && texturePos.y == 100) {
			texturePos.x = 100;

		} else if (texturePos.x == 100 && texturePos.y == 100) {
			texturePos.x = 0;
			texturePos.y = 0;

		}

		selectorRect.setTextureRect(textureRect);
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && getKeyTime()) {
		tileMap.addTile(mousePosGrid.x, mousePosGrid.y, 0, textureRect);

	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && getKeyTime()) {
		tileMap.removeTile(mousePosGrid.x, mousePosGrid.y, 0);

	}
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
