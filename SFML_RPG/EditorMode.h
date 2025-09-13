#pragma once


#include "State.h"
#include "TileMap.h"
#include "KeyTime.h"

class EditorData
{ 
public:
	EditorData() = default;

	sf::View* view;
	sf::Font* font;
	std::map<std::string, sf::Keyboard::Scancode>* keybinds;
	KeyTime* keyTime;

	sf::Vector2i* mousePosScreen;
	sf::Vector2i* mousePosWindow;
	sf::Vector2f* mousePosView;
	sf::Vector2i* mousePosGrid;
};

class EditorMode
{
protected:
	StateData& stateData;
	EditorData& editorData;
	TileMap& tileMap;

public:
	EditorMode(StateData& stateData, EditorData& editorData, TileMap& tileMap);
	virtual ~EditorMode();

	virtual void updateInput(const float& dt) = 0;
	virtual void updateGui(const float& dt) = 0;
	virtual void update(const float& dt) = 0;

	virtual void renderGui(sf::RenderTarget& target) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

