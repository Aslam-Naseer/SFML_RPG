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

	// EXP Bar
	std::string expBarString;
	sf::Text expBarText;
	sf::RectangleShape expBarMax;
	sf::RectangleShape expBarMain;
	sf::Text levelText;

	void initFont();
	void initHpBar();
	void initExpBar();

public:
	PlayerGui(Player* player);
	~PlayerGui();

	void updateHpBar();
	void updateExpBar();
	void update(const float& dt);

	void renderHpBar(sf::RenderTarget& target);
	void renderExpBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

