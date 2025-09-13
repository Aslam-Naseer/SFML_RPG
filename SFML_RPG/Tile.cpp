#include "stdafx.h"
#include "Tile.h"

Tile::Tile(float x, float y, const sf::Texture& tileSheet, 
	const sf::IntRect& textureRect, Type type, bool collision):
	shape(tileSheet)
{
	shape.setPosition({ x,y });
	shape.setTextureRect(textureRect);

	this->type = type;
	this->collision = collision;
}

Tile::~Tile()
{
}

std::string Tile::toString()
{
	std::stringstream ss;
	ss << shape.getTextureRect().position.x << " " << shape.getTextureRect().position.y 
		<< " " << static_cast<short>(type) << " " << collision << " ";

	return ss.str();
}

void Tile::setPosition(float x, float y)
{
	shape.setPosition({ x,y });
}

bool Tile::intersects(const sf::FloatRect bounds) const
{
	return shape.getGlobalBounds().findIntersection(bounds).has_value();
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target, sf::Shader* shader)
{
	target.draw(this->shape, shader);
}
