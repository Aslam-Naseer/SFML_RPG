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

	textureSelector = new gui::TextureSelector(50.f, 50.f, 400.f, 500.f, tileMap.getTileSheet(), gridSize, font);
}

EditorState::EditorState(StateData& state_data, sf::Font& font) :
	State(state_data), pmenu(*window, font), tileMap(state_data.gridSize), gridSize(state_data.gridSize), font(font)
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

void EditorState::updateGui(const float& dt)
{
	textureSelector->update(mousePosWindow, dt);

	if (!textureSelector->isActive())
	{
		selectorRect.setPosition({
			mousePosGrid.x * gridSize,
			mousePosGrid.y * gridSize,
		});

	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && getKeyTime()) {
		if (!textureSelector->isActive())
		{
			tileMap.addTile(mousePosGrid.x, mousePosGrid.y, 0, textureRect);
		}
		else
		{
			textureRect.position.x = textureSelector->getTextureRect().position.x;
			textureRect.position.y = textureSelector->getTextureRect().position.y;
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && getKeyTime()) {
		if (!textureSelector->isActive())
			tileMap.removeTile(mousePosGrid.x, mousePosGrid.y, 0);

	}

	selectorRect.setTextureRect(textureRect);

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
		updateGui(dt);
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
	textureSelector->render(*target);

	if(!textureSelector->isActive())
		target->draw(selectorRect);

	if (paused)
	{
		pmenu.render(*target);
	}

	//DEBUG: REMOVE LATER
	sf::Text mouseText(font,"",15);
	mouseText.setPosition({mousePosView.x + 20, mousePosView.y - 20});
	std::stringstream st;
	st << textureRect.position.x << ' ' << textureRect.position.y;
	mouseText.setString(st.str());

	target->draw(mouseText);

}
