#pragma once

#include "Player.h"
#include "Gui.h"

class PlayerGui
{
private:
	const Player* player;
	sf::Font font;

	gui::ProgressBar* hpBar;
	std::string hpBarString;

	gui::ProgressBar* expBar;
	std::string expBarString;
	sf::Text levelText;

	void initFont();
	void initHpBar();
	void initExpBar();

public:
	PlayerGui(Player* player);
	~PlayerGui();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

