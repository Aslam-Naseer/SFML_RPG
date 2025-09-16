#pragma once

#include "Player.h"

class PlayerTab
{
private:
	const Player* player;

	sf::RectangleShape background;
	sf::Vector2f textPadding;
	sf::Text text;

	float speed;
	bool hidden = true;
	bool animate = false;

	void initGui();

public:
	PlayerTab(const Player* player, sf::Font& font, float animateTime = .35f);
	~PlayerTab();

	void toggleTab();

	void updateAnimations(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

