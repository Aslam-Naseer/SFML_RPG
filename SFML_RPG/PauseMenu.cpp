#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::Font& font) :
	menuText(font), font(font)
{
	float windowWidth = utils::p2pX(100.f);
	float windowHeight = utils::p2pY(100.f);

	background.setFillColor(sf::Color(20, 20, 20, 100));
	background.setSize({windowWidth, windowHeight});

	container.setFillColor(sf::Color(50, 50, 50, 200));
	container.setSize({ windowWidth * 0.3f, windowHeight - utils::p2pY(28.f)});
	container.setPosition({ windowWidth / 2.f - container.getSize().x / 2.f, utils::p2pY(14.f)});

	menuText.setString("PAUSED");
	menuText.setCharacterSize(utils::calcCharSize(2.7f));
	menuText.setFillColor(sf::Color::White);
	menuText.setPosition({
		container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().size.x / 2.f,
		container.getPosition().y + utils::p2pY(5.f)
		});
}

PauseMenu::~PauseMenu()
{
	for(auto &i: buttons)
	{
		delete i.second;
	}
}

bool PauseMenu::isButtonPressed(std::string key) const
{
    auto it = buttons.find(key);
    if (it != buttons.end() && it->second)
        return it->second->isPressed() && keyTime.isReady();
    return false;
}

void PauseMenu::addButton(const std::string key, const float y, const std::string text)
{
	float width = utils::p2pX(14.1f);
	float height = utils::p2pY(9.3f);
	float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;

	buttons[key] = new gui::Button(
		x, y, width, height,
		text, font, utils::calcCharSize(2),
		sf::Color(150, 150, 150, 200), sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);
}

void PauseMenu::update(const sf::Vector2i& mousePos, const float& dt)
{
	for(auto &i: buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	target.draw(menuText);
	for(auto &i: buttons)
	{
		i.second->render(target);
	}

}
