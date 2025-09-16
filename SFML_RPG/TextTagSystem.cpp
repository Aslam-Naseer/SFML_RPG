#include "stdafx.h"
#include "TextTagSystem.h"


TextTagSystem::TextTag::TextTag(sf::Font& font, std::string str, sf::Color color, unsigned charSize,
	sf::Vector2f position, sf::Vector2f direction, float lifetime, float speed):
	text(font), direction(direction), lifetime(lifetime), speed(speed)
{
	text.setFillColor(color);
	text.setCharacterSize(charSize);
	text.setStyle(sf::Text::Bold);
	text.setPosition(position);
	text.setString(str);
}

void TextTagSystem::TextTag::update(const float& dt)
{
	lifetime -= dt;
	text.move(direction * speed * dt);
}

void TextTagSystem::TextTag::render(sf::RenderTarget& target)
{
	target.draw(text);
}


void TextTagSystem::createTextTag(TagType type, float x, float y, std::string str)
{
	sf::Color color;
	unsigned charSize;
	sf::Vector2f direction;
	float lifetime;
	float speed;

	switch (type)
	{
	case TagType::DefaultTag:
		color = sf::Color::White;
		charSize = utils::calcCharSize(1.1f);
		direction = sf::Vector2f(0.f, -1.f);
		lifetime = 1.f;
		speed = 50.f;
		break;

	case TagType::NegativeTag:
		color = sf::Color(250, 50, 50, 200);
		charSize = utils::calcCharSize(1.1);
		direction = sf::Vector2f(0.f, -1.f);
		lifetime = 1.f;
		speed = 50.f;
		break;

	case TagType::PositiveTag:
		color = sf::Color(50, 250, 50, 200);
		charSize = utils::calcCharSize(1.1f);
		direction = sf::Vector2f(0.f, -1.f);
		lifetime = 1.f;
		speed = 50.f;
		break;

	case TagType::ExperienceTag:
		color = sf::Color(50, 250 , 250, 200);
		charSize = utils::calcCharSize(1.f);
		direction = sf::Vector2f(0.f, -1.f);
		lifetime = 1.5f;
		speed = 30.f;
		break;

	default:
		color = sf::Color::White;
		charSize = utils::calcCharSize(1.2f);
		direction = sf::Vector2f(0.f, -1.f);
		lifetime = 1.f;
		speed = 50.f;
		break;
	}

	textTags.emplace_back(font, str, color, charSize,
		sf::Vector2f(x, y), direction, lifetime, speed);
}

TextTagSystem::TextTagSystem(sf::Font& font):
	font(font)
{
}

TextTagSystem::~TextTagSystem()
{
}


void TextTagSystem::update(const float& dt)
{
	for (auto& tag : textTags)
		tag.update(dt);

	textTags.erase(std::remove_if(textTags.begin(), textTags.end(),
		[](const TextTag& tag) { return tag.lifetime <= 0.f; }), textTags.end());
}

void TextTagSystem::render(sf::RenderTarget& target)
{
	for (auto& tag : textTags)
		tag.render(target);
}