#pragma once

#include "Gui.h"

class PauseMenu
{
private:
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

	sf::Text menuText;

	void initButtons(sf::Font& font);
	void addButton(const std::string key, const float y, const std::string text, sf::Font& font);

public:
	PauseMenu(sf::RenderTarget& window, sf::Font& font);
	virtual ~PauseMenu();

	bool isButtonPressed(const std::string key) const;

	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

