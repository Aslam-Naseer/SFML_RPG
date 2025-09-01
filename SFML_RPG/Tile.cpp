#include "stdafx.h"
#include "Tile.h"

Tile::Tile(float x, float y, float gridSize)
{
	shape.setPosition({ x,y });
	shape.setSize({ gridSize, gridSize });
	shape.setFillColor(sf::Color::Green);
	
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(sf::Color::Black);
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
