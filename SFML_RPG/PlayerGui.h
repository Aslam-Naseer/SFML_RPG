#pragma once

#include "Player.h"

class PlayerGui
{
private:
	const Player* player;
	sf::Font font;

	// HP Bar
	std::string hpBarString;
	sf::Text hpBarText;
	sf::RectangleShape hpBarMax;
	sf::RectangleShape hpBarMain;

	void initFont();
	void initHpBar();

public:
	PlayerGui(Player* player);
	~PlayerGui();

	void updateHpBar();
	void update(const float& dt);

	void renderHpBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

