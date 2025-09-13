#pragma once

#include "EditorMode.h"
#include "Gui.h"

class DefaultEditorMode :
    public EditorMode
{
private:
	sf::RectangleShape selectorRect;
	sf::RectangleShape sidebar;
	sf::IntRect textureRect;
	gui::TextureSelector* textureSelector;

	short type = 0;
	bool collision = false;

	void initGui();

public:
    DefaultEditorMode(StateData& stateData, EditorData& editorData, TileMap& tileMap);
    ~DefaultEditorMode();


	void updateInput(const float& dt) override;
	void updateGui(const float& dt) override;
	void update(const float& dt) override;

	void renderGui(sf::RenderTarget& target) override;
	void render(sf::RenderTarget& target) override;

};

