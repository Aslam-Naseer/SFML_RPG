#include "Gui.h"

// BUTTON

gui::Button::Button(
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

gui::Button::~Button()
{ }

bool gui::Button::isPressed() const
{
	return buttonState == ButtonState::ACTIVE;
}

void gui::Button::update(const sf::Vector2f& mousePos)
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

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(shape);
	target.draw(text);
}

// DROP DOWN LIST

bool gui::DropDownList::getKeyTime()
{
	if(keyTime >= keyTimeMax)
	{
		keyTime = 0.f;
		return true;
	}

	return false;
}

void gui::DropDownList::updateKeyTime(const float& dt)
{
	if(keyTime < keyTimeMax)
	{
		keyTime += 10.f * dt;
	}

}

gui::DropDownList::DropDownList(
	float x, float y, float width, float height,
	sf::Font& font, const std::vector<std::string>& list, unsigned int index
) : font(font), showList(false), keyTime(0.f), keyTimeMax(1.f)
{
	activeElement = new gui::Button(
		x, y, width, height,
		list[index], font, 16,
		sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
	);

	for (unsigned i = 0; i < list.size(); ++i)
	{
		this->list.push_back(new gui::Button(
			x, y + (i * height), width, height,
			list[i], font, 16,
			sf::Color::White, sf::Color::White, sf::Color::White,
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
		));
	}
}

gui::DropDownList::~DropDownList()
{
	delete activeElement;
	for (auto& i : list)
	{
		delete i;
	}
}

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{
	updateKeyTime(dt);
	activeElement->update(mousePos);

	if (activeElement->isPressed() && getKeyTime())
	{
		showList = !showList;
	}

	if (showList)
	{
		for (auto& i : list)
		{
			i->update(mousePos);
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	activeElement->render(target);
	if (showList)
	{
		for (auto& i : list)
		{
			i->render(target);
		}
	}

}