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

bool Tile::resolveCollision(const sf::FloatRect& bounds, sf::Vector2f& currentPosition) const
{
	if(!collision || !intersects(bounds))
		return false;

	bool resolveX = false, resolveY = false;
	sf::FloatRect tileBounds = shape.getGlobalBounds();

	float nextLeft = bounds.position.x;
	float nextRight = bounds.position.x + bounds.size.x;
	float nextTop = bounds.position.y;
	float nextBot = bounds.position.y + bounds.size.y;

	float tileLeft = tileBounds.position.x;
	float tileRight = tileBounds.position.x + tileBounds.size.x;
	float tileTop = tileBounds.position.y;
	float tileBot = tileBounds.position.y + tileBounds.size.y;

	float overlapLeft = nextRight - tileLeft;
	float overlapRight = tileRight - nextLeft;
	float overlapTop = nextBot - tileTop;
	float overlapBottom = tileBot - nextTop;

	float minOverlapX = std::min(overlapLeft, overlapRight);
	float minOverlapY = std::min(overlapTop, overlapBottom);

	if (minOverlapX < minOverlapY)
	{
		if (overlapLeft < overlapRight)
			currentPosition.x = tileLeft - bounds.size.x;
		else
			currentPosition.x = tileRight;

		resolveX = true;
	}
	else
	{
		if (overlapTop < overlapBottom)
			currentPosition.y = tileTop - bounds.size.y;
		else
			currentPosition.y = tileBot;

		resolveY = true;
	}

	return resolveX || resolveY;
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target, sf::Shader* shader)
{
	target.draw(this->shape, shader);
}
