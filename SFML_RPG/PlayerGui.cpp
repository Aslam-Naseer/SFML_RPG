#include "stdafx.h"
#include "PlayerGui.h"

void PlayerGui::initFont()
{
	if (!font.openFromFile("Fonts/Dosis-Light.ttf")) {
		throw std::runtime_error("ERROR::GAME::FONT_NOT_AVAILABLE");
	}
}

void PlayerGui::initHpBar()
{
	float x = 20.f, y = 20.f;
	float width = 300.f, height = 50.f;

	hpBarMax.setSize({ width, height });
	hpBarMax.setFillColor(sf::Color(50, 50, 50, 200));
	hpBarMax.setPosition({ x, y });
	hpBarMax.setOutlineThickness(5.f);
	hpBarMax.setOutlineColor(sf::Color(150, 150, 150, 255));

	hpBarMain.setSize({ width, height });
	hpBarMain.setFillColor(sf::Color(250, 50, 50, 200));
	hpBarMain.setPosition({ x, y });

	hpBarText.setCharacterSize(24);
	hpBarText.setPosition({ x + 20.f, y + height / 2.f - 14});
}

PlayerGui::PlayerGui(Player* player):
	hpBarText(font), player(player)
{
	initFont();
	initHpBar();
}

PlayerGui::~PlayerGui()
{
}

void PlayerGui::updateHpBar()
{
	const AttributeComponent* ac = player->getAttributeComponent();

	hpBarMain.setSize({
		std::floor(static_cast<float>(ac->hp) / ac->hpMax * hpBarMax.getSize().x),
		hpBarMain.getSize().y
		});

	hpBarString = "HP: " + std::to_string(ac->hp) + " / " + std::to_string(ac->hpMax);
	hpBarText.setString(hpBarString);
}

void PlayerGui::update(const float& dt)
{
	updateHpBar();
}

void PlayerGui::renderHpBar(sf::RenderTarget& target)
{
	target.draw(hpBarMax);
	target.draw(hpBarMain);
	target.draw(hpBarText);
}

void PlayerGui::render(sf::RenderTarget& target)
{
	renderHpBar(target);
}
