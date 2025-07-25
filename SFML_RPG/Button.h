#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

enum class ButtonState
{
	IDLE = 0,
	HOVER,
	ACTIVE
};;

class Button
{
private:
	sf::RectangleShape shape;
	sf::Font& font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	ButtonState buttonState;

public:

	Button(float x, float y, float width, float height,
		const std::string &text, sf::Font &font,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);

};

