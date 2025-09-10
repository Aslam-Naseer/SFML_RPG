#pragma once

#include "Gui.h"
#include "KeyTime.h"

class PauseMenu
{
private:
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;
	sf::Font& font;

	sf::Text menuText;
	KeyTime keyTime;

public:
	PauseMenu(sf::Font& font);
	virtual ~PauseMenu();

	bool isButtonPressed(const std::string key) const;
	void addButton(const std::string key, const float y, const std::string text);

	void update(const sf::Vector2i& mousePos, const float& dt);
	void render(sf::RenderTarget& target);
};

