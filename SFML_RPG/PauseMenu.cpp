#include "stdafx.h"
#include "PauseMenu.h"

void PauseMenu::initButtons(sf::Font& font)
{
	addButton("QUIT", 700.f, "Quit", font);
}

PauseMenu::PauseMenu(sf::RenderTarget& window, sf::Font& font) :
	menuText(font)
{
	float windowWidth = static_cast<float>(window.getSize().x);
	float windowHeight = static_cast<float>(window.getSize().y);

	background.setFillColor(sf::Color(20, 20, 20, 100));
	background.setSize({windowWidth, windowHeight});

	container.setFillColor(sf::Color(50, 50, 50, 200));
	container.setSize({ windowWidth / 4.f, windowHeight - 300.f });
	container.setPosition({ windowWidth / 2.f - container.getSize().x / 2.f, 150.f });

	menuText.setString("PAUSED");
	menuText.setCharacterSize(70);
	menuText.setFillColor(sf::Color::White);
	menuText.setPosition({
		container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().size.x / 2.f,
		container.getPosition().y + 25.f
		});

	initButtons(font);
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

void PauseMenu::addButton(const std::string key, const float y, const std::string text, sf::Font& font)
{
	float width = 270;
	float height = 100;
	float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;

	buttons[key] = new gui::Button(
		x, y, width, height,
		text, font, 50,
		sf::Color(70, 70, 70, 255), sf::Color(200, 200, 200, 255), sf::Color(20, 20, 20, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0)
	);
}

void PauseMenu::update(const sf::Vector2i& mousePos, const float& dt)
{
	keyTime.update(dt);
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
