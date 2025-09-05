#include "stdafx.h"
#include "Tile.h"

Tile::Tile(float x, float y, float gridSize, const sf::Texture& tileSheet, 
	const sf::IntRect& textureRect, short type, bool collision)
{
	shape.setPosition({ x,y });
	shape.setSize({ gridSize, gridSize });

	if(collision)
	{
		shape.setOutlineThickness(1.f);
		shape.setOutlineColor(sf::Color::Red);
	}

	shape.setTexture(&tileSheet);
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
		<< " " << type << " " << collision << " ";

	return ss.str();
}

void Tile::setPosition(float x, float y)
{
	shape.setPosition({ x,y });
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
