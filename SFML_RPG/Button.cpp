#include "Button.h"



Button::Button(
	float x, float y, float width, float height,
	const std::string& text_str, sf::Font& font, unsigned int char_size, 
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, 
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color
)
	: text(font, text_str, char_size), font(font),
	textIdleColor(text_idle_color), textHoverColor(text_hover_color), textActiveColor(text_active_color),
	idleColor(idle_color), hoverColor(hover_color), activeColor(active_color)
{
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(idleColor);

	text.setPosition(
		{ shape.getPosition().x + shape.getSize().x / 2.f ,
		shape.getPosition().y + shape.getSize().y / 2.f }
	);

	text.setOrigin(
		{ text.getGlobalBounds().size.x / 2.f , text.getGlobalBounds().size.y / 2.f }
	);

	buttonState = ButtonState::IDLE;
}

Button::~Button()
{ }

bool Button::isPressed() const
{
	return buttonState == ButtonState::ACTIVE;
}

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
		text.setFillColor(textIdleColor);
		break;
	case ButtonState::HOVER:
		shape.setFillColor(hoverColor);
		text.setFillColor(textHoverColor);
		break;
	case ButtonState::ACTIVE:
		shape.setFillColor(activeColor);
		text.setFillColor(textActiveColor);
		break;
	default:
		shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(shape);
	target.draw(text);
}
