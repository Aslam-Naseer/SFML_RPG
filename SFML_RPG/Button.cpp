#include "Button.h"

Button::Button(float x, float y, float width, float height,const std::string& text_string, sf::Font& font, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor):
	text(font, text_string),font(font), idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor)
{
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(idleColor);

	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(24);
	text.setPosition(
		{ shape.getPosition().x + shape.getSize().x / 2.f - text.getGlobalBounds().size.x / 2.f,
		shape.getPosition().y + shape.getSize().y / 2.f - text.getGlobalBounds().size.y / 2.f }
	);

	buttonState = ButtonState::IDLE;
}

Button::~Button()
{ }

void Button::update(const sf::Vector2f& mousePos)
{
	buttonState = ButtonState::IDLE;

	if (shape.getGlobalBounds().contains(mousePos))
	{
		buttonState = ButtonState::HOVER;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			buttonState = ButtonState::ACTIVE;
		}
	}

	switch (buttonState)
	{
	case ButtonState::IDLE:
		shape.setFillColor(idleColor);
		break;
	case ButtonState::HOVER:
		shape.setFillColor(hoverColor);
		break;
	case ButtonState::ACTIVE:
		shape.setFillColor(activeColor);
		break;
	default:
		shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(shape);
	target->draw(text);
}
