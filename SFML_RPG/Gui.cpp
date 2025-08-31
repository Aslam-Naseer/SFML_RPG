#include "Gui.h"

// BUTTON

gui::Button::Button(
	float x, float y, float width, float height,
	const std::string& text_str, sf::Font& font, unsigned int char_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color
)
	: text(font, text_str, char_size), font(font),
	textIdleColor(text_idle_color), textHoverColor(text_hover_color), textActiveColor(text_active_color),
	idleColor(idle_color), hoverColor(hover_color), activeColor(active_color),
	outlineIdleColor(outline_idle_color), outlineHoverColor(outline_hover_color), outlineActiveColor(outline_active_color)
{

	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(idleColor);

	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(outlineIdleColor);

	text.setPosition(
		{ shape.getPosition().x + shape.getSize().x / 2.f ,
		shape.getPosition().y + shape.getSize().y / 2.f }
	);

	text.setOrigin(
		{ text.getGlobalBounds().size.x / 2.f , text.getGlobalBounds().size.y * 2.f / 3.f }
	);

	buttonState = ButtonState::IDLE;
}

gui::Button::~Button()
{ }

// Accessors/ Modifiers

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
	this->text.setOrigin(
		{ this->text.getGlobalBounds().size.x / 2.f , this->text.getGlobalBounds().size.y * 2.f / 3.f }
	);
}

bool gui::Button::isPressed() const
{
	return buttonState == ButtonState::ACTIVE;
}

short unsigned gui::Button::getId() const
{
	return id;
}

const std::string gui::Button::getText() const
{
	return text.getString();
}

// Functions

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
		shape.setOutlineColor(outlineIdleColor);
		break;
	case ButtonState::HOVER:
		shape.setFillColor(hoverColor);
		text.setFillColor(textHoverColor);
		shape.setOutlineColor(outlineHoverColor);
		break;
	case ButtonState::ACTIVE:
		shape.setFillColor(activeColor);
		text.setFillColor(textActiveColor);
		shape.setOutlineColor(outlineActiveColor);
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
	float x, float y, float width, float height, unsigned int char_size,
	sf::Font& font, const std::vector<std::string>& list, unsigned int index
) : font(font), showList(false), keyTime(0.f), keyTimeMax(1.5f)
{
	activeElement = new gui::Button(
		x, y, width, height,
		list[index], font, char_size,
		sf::Color(200, 200, 200, 255), sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
		sf::Color(70, 70, 70, 0), sf::Color(200, 200, 200, 0), sf::Color(20, 20, 20, 0),
		sf::Color::White, sf::Color::White, sf::Color::White
	);

	for (unsigned i = 0; i < list.size(); ++i)
	{
		this->list.push_back(new gui::Button(
			x, y + ((i+1) * height) + 1, width, height,
			list[i], font, char_size,
			sf::Color::White, sf::Color::White, sf::Color::White,
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
		));

		this->list.back()->setId(i);
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
			if(i->isPressed() && getKeyTime())
			{
				showList = false;
				activeElement->setText(i->getText());
			}
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