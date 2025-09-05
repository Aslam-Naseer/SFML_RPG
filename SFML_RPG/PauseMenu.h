#pragma once

#include "Gui.h"
#include "KeyTime.h"

class PauseMenu
{
private:
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

	sf::Text menuText;
	KeyTime keyTime;

	void initButtons(sf::Font& font);

public:
	PauseMenu(sf::RenderTarget& window, sf::Font& font);
	virtual ~PauseMenu();

	bool isButtonPressed(const std::string key) const;
	void addButton(const std::string key, const float y, const std::string text, sf::Font& font);

	void update(const sf::Vector2i& mousePos, const float& dt);
	void render(sf::RenderTarget& target);
};

