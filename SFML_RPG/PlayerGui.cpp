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
	float x = 40.f, y = 50.f;
	float width = 300.f, height = 40.f;
	unsigned fontSize = 24;

	hpBarMax.setSize({ width, height });
	hpBarMax.setFillColor(sf::Color(50, 50, 50, 200));
	hpBarMax.setPosition({ x, y });
	hpBarMax.setOutlineThickness(5.f);
	hpBarMax.setOutlineColor(sf::Color(150, 150, 150, 255));

	hpBarMain.setSize({ width, height });
	hpBarMain.setFillColor(sf::Color(250, 50, 50, 200));
	hpBarMain.setPosition({ x, y });

	hpBarText.setCharacterSize(fontSize);
	hpBarText.setPosition({ x + 20.f, y + height / 2.f - fontSize / 2.f});
}

void PlayerGui::initExpBar()
{
	float x = 40.f, y = 110.f;
	float width = 300.f, height = 35.f;
	unsigned fontSize = 18;

	expBarMax.setSize({ width, height });
	expBarMax.setFillColor(sf::Color(50, 50, 50, 200));
	expBarMax.setPosition({ x, y });
	expBarMax.setOutlineThickness(5.f);
	expBarMax.setOutlineColor(sf::Color(150, 150, 150, 255));

	expBarMain.setSize({ width, height });
	expBarMain.setFillColor(sf::Color(50, 50, 250, 200));
	expBarMain.setPosition({ x, y });

	expBarText.setCharacterSize(fontSize);
	expBarText.setPosition({ x + 20.f, y + height / 2.f - 10 });

	levelText.setCharacterSize(fontSize);
	levelText.setPosition({ x + (width * 0.75f) , y + height / 2.f - fontSize / 2.f });
}

PlayerGui::PlayerGui(Player* player):
	player(player), hpBarText(font), expBarText(font), levelText(font)
{
	initFont();
	initHpBar();
	initExpBar();
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

void PlayerGui::updateExpBar()
{
	const AttributeComponent* ac = player->getAttributeComponent();

	expBarMain.setSize({
		std::floor(static_cast<float>(ac->exp) / ac->expNext * expBarMax.getSize().x),
		expBarMain.getSize().y
		});

	expBarString = "EXP: " + std::to_string(ac->exp) + " / " + std::to_string(ac->expNext);
	expBarText.setString(expBarString);

	levelText.setString("Level: " + std::to_string(ac->level));
}

void PlayerGui::update(const float& dt)
{
	updateHpBar();
	updateExpBar();
}

void PlayerGui::renderHpBar(sf::RenderTarget& target)
{
	target.draw(hpBarMax);
	target.draw(hpBarMain);
	target.draw(hpBarText);
}

void PlayerGui::renderExpBar(sf::RenderTarget& target)
{
	target.draw(expBarMax);
	target.draw(expBarMain);
	target.draw(expBarText);

	target.draw(levelText);
}

void PlayerGui::render(sf::RenderTarget& target)
{
	renderHpBar(target);
	renderExpBar(target);
}
