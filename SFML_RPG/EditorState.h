#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "Gui.h"

class EditorState :
	public State
{
private:
	PauseMenu pmenu;
	TileMap tileMap;
	gui::TextureSelector* textureSelector;
	float gridSize;

	sf::RectangleShape selectorRect;
	sf::IntRect textureRect;

	void initKeybinds();
	void initTextures();
	void initGui();

public:
	EditorState(StateData& state_data, sf::Font& font);
	virtual ~EditorState();

	void updatePauseMenuButtons();
	void updateGui();
	void updateInput(const float& dt) override;

	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

