#include "stdafx.h"
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

	sf::FloatRect textBounds = text.getLocalBounds();

	text.setOrigin({
		textBounds.position.x + textBounds.size.x / 2.f,
		textBounds.position.y + textBounds.size.y / 2.f
		});

	text.setPosition({
		shape.getPosition().x + shape.getSize().x / 2.f,
		shape.getPosition().y + shape.getSize().y / 2.f
		});

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

	sf::FloatRect textBounds = this->text.getLocalBounds();
	this->text.setOrigin({
		textBounds.position.x + textBounds.size.x / 2.f,
		textBounds.position.y + textBounds.size.y / 2.f
		});

	this->text.setPosition({
		shape.getPosition().x + shape.getSize().x / 2.f,
		shape.getPosition().y + shape.getSize().y / 2.f
		});
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
	activeElement->setId(index);

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

short unsigned gui::DropDownList::getActiveId()
{
	return activeElement->getId();
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
				activeElement->setId(i->getId());
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

// Texture Selector

gui::TextureSelector::TextureSelector(float x, float y, float width, float height,const sf::Texture& textureSheet, float grid_size):
	active(false), gridSize(grid_size), sheet(textureSheet)
{
	bounds.setPosition({ x,y });
	bounds.setSize({ width, height });
	bounds.setFillColor(sf::Color(55, 55, 55, 100));
	bounds.setOutlineThickness(1.f);
	bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	sheet.setPosition({x,y});
	if (sheet.getLocalBounds().size.x > bounds.getLocalBounds().size.x)
		sheet.setTextureRect(sf::IntRect({ 0,0 }, { static_cast<int>(bounds.getLocalBounds().size.x) ,static_cast<int>(sheet.getLocalBounds().size.y) }));
	if (sheet.getLocalBounds().size.y > bounds.getLocalBounds().size.y)
		sheet.setTextureRect(sf::IntRect({ 0,0 }, { static_cast<int>(sheet.getLocalBounds().size.x) ,static_cast<int>(bounds.getLocalBounds().size.y) }));

	selector.setPosition({ x,y });
	selector.setSize({ gridSize, gridSize });
	selector.setFillColor(sf::Color::Transparent);
	selector.setOutlineThickness(3.f);
	selector.setOutlineColor(sf::Color::White);

	textureRect.position = { 0,0 };
	textureRect.size = { static_cast<int>(gridSize), static_cast<int>(gridSize) };
}

gui::TextureSelector::~TextureSelector()
{
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return textureRect;
}

bool gui::TextureSelector::isActive() const
{
	return active;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow)
{
	if(bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)) )
		active = true;
	else
		active = false;

	if (active)
	{
		unsigned mousePosGridX = (mousePosWindow.x - static_cast<unsigned>(bounds.getGlobalBounds().position.x)) / static_cast<unsigned>(gridSize);
		unsigned mousePosGridY = (mousePosWindow.y - static_cast<unsigned>(bounds.getGlobalBounds().position.y)) / static_cast<unsigned>(gridSize);

		selector.setPosition({
			bounds.getGlobalBounds().position.x + mousePosGridX * gridSize,
			bounds.getGlobalBounds().position.x + mousePosGridY * gridSize
		});

		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && sheet.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			textureRect.position.x = static_cast<int>(selector.getPosition().x - bounds.getGlobalBounds().position.x);
			textureRect.position.y = static_cast<int>(selector.getPosition().y - bounds.getGlobalBounds().position.y);
		}
	}
	else 
	{
		selector.setPosition({
			bounds.getGlobalBounds().position.x + static_cast<float>(textureRect.position.x),
			bounds.getGlobalBounds().position.y + static_cast<float>(textureRect.position.y)
		});
	}
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	target.draw(bounds);
	target.draw(sheet);
	target.draw(selector);
}