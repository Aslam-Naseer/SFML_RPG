#pragma once

class Tile
{
private:

protected:
	sf::RectangleShape shape;

public:
	Tile(float x, float y, float gridSize, const sf::Texture& tileSheet, const sf::IntRect& textureRect);
	virtual ~Tile();

	std::string toString();
	void setPosition(float x, float y);

	void update();
	void render(sf::RenderTarget& target);
};

