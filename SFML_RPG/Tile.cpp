#include "stdafx.h"
#include "Tile.h"

Tile::Tile(float x, float y, float gridSize, const sf::Texture& tileSheet, const sf::IntRect& textureRect)
{
	shape.setPosition({ x,y });
	shape.setSize({ gridSize, gridSize });

	//shape.setOutlineThickness(1.f);
	//shape.setOutlineColor(sf::Color::Black);

	shape.setTexture(&tileSheet);
	shape.setTextureRect(textureRect);
}

Tile::~Tile()
{
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
