#include "stdafx.h"
#include "PlayerTab.h"

PlayerTab::PlayerTab(const Player* player, sf::Font& font, float animateTime):
	player(player), text(font)
{
	background.setSize({ utils::p2pX(30.f), utils::p2pY(100.f) });
	background.setFillColor(sf::Color(20, 20, 20, 220));
	background.setOutlineThickness(2.f);
	background.setOutlineColor(sf::Color(200, 200, 200, 200));
	background.setPosition({ -1 * background.getSize().x, 0.f});

	textPadding = { 30.f, utils::p2pY(10.f)};

	text.setCharacterSize(utils::calcCharSize(1.4f));
	text.setFillColor(sf::Color(200, 200, 200, 255));
	text.setPosition({ background.getPosition().x + textPadding.x, background.getPosition().y + textPadding.y });

	speed = background.getSize().x / animateTime;
}

PlayerTab::~PlayerTab()
{
}

void PlayerTab::toggleTab()
{
	if (animate)
		return;

	animate = true;
	hidden = !hidden;
}


void PlayerTab::updateAnimations(const float& dt)
{
	if (!animate)
		return;

	if (hidden)
	{
		background.move({ -1 * speed * dt, 0.f });
		animate = background.getPosition().x + background.getSize().x > 0;
	}
	else
	{
		background.move({ speed * dt , 0.f });
		animate = background.getPosition().x <= 0;
	}

	if (!animate)
		background.setPosition({ hidden ? -1 * background.getSize().x : 0.f, 0.f });
	
	text.setPosition({ background.getPosition().x + textPadding.x, background.getPosition().y + textPadding.y });
	
}


void PlayerTab::update(const float& dt)
{
	if (animate)
		updateAnimations(dt);

	if (!hidden)
		text.setString(player->getStats());
}

void PlayerTab::render(sf::RenderTarget& target)
{
	if (!hidden || animate)
	{
		target.draw(background);
		target.draw(text);
	}
}