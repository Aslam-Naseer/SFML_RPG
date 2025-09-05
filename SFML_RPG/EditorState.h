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
	float viewSpeed;
	sf::View view;
	sf::RectangleShape selectorRect;
	sf::RectangleShape sidebar;

	short type;
	bool collision;
	sf::IntRect textureRect;
	sf::Font& font;

	void initView();
	void initKeybinds();
	void initTextures();
	void initGui();

public:
	EditorState(StateData& state_data, sf::Font& font);
	virtual ~EditorState();

	void updatePauseMenuButtons();
	void updateGui(const float& dt);
	void updateInput(const float& dt) override;

	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

