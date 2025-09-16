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
	float x = utils::p2pX(78.f), y = utils::p2pY(4.f);
	float width = utils::p2pX(20.f), height = utils::p2pY(3.9f);
	unsigned fontSize = utils::calcCharSize(1.f);

	hpBar = new gui::ProgressBar(x, y, width, height, 7, sf::Color(0, 228, 48), &font, fontSize);
}

void PlayerGui::initExpBar()
{
	float x = utils::p2pX(78.f), y = utils::p2pY(10.f);
	float width = utils::p2pX(20.f), height = utils::p2pY(3.6f);
	unsigned fontSize = utils::calcCharSize(0.75f);

	expBar = new gui::ProgressBar(x, y, width, height, 20, sf::Color(0, 120, 248), &font, fontSize);

	levelText.setCharacterSize(fontSize);
	levelText.setPosition({ x + (width * 0.75f) , y + height / 2.f - fontSize / 2.f });
}

PlayerGui::PlayerGui(const Player* player):
	player(player), levelText(font), playerTab(player, font)
{
	initFont();
	initHpBar();
	initExpBar();
}

PlayerGui::~PlayerGui()
{
	delete hpBar;
	delete expBar;
}


void PlayerGui::toggleTab()
{
	playerTab.toggleTab();
}

void PlayerGui::update(const float& dt)
{
	const AttributeComponent* ac = player->getAttributeComponent();

	hpBarString = "HP: " + std::to_string(ac->hp) + " / " + std::to_string(ac->hpMax);
	expBarString = "EXP: " + std::to_string(ac->exp) + " / " + std::to_string(ac->expNext);

	hpBar->setProgress(static_cast<float>(ac->hp), static_cast<float>(ac->hpMax), hpBarString);
	expBar->setProgress(static_cast<float>(ac->exp), static_cast<float>(ac->expNext), expBarString);

	levelText.setString("Level: " + std::to_string(ac->level));
	playerTab.update(dt);
}

void PlayerGui::render(sf::RenderTarget& target)
{
	hpBar->render(target);
	expBar->render(target);
	playerTab.render(target);

	target.draw(levelText);
}
