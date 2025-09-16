#pragma once

#include "PlayerTab.h"
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
	PlayerTab playerTab;

	void initFont();
	void initHpBar();
	void initExpBar();

public:
	PlayerGui(const Player* player);
	~PlayerGui();

	void toggleTab();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

