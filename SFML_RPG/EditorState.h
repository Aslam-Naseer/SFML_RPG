#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "Gui.h"
#include "EditorMode.h"
#include "DefaultEditorMode.h"
#include "EnemyEditorMode.h"

class EditorState :
	public State
{
private:
	PauseMenu pmenu;
	TileMap tileMap;
	
	float gridSize;
	sf::Font& font;
	float viewSpeed;
	sf::View view;

	EditorData editorData;
	std::vector<EditorMode*> modes;
	size_t activeMode = 0;

	void initView();
	void initKeybinds();
	void initEditorData();
	void initModes();
	void initGui();

public:
	EditorState(StateData& state_data, sf::Font& font);
	virtual ~EditorState();

	void updateGui(const float& dt);
	void updateInput(const float& dt) override;

	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

