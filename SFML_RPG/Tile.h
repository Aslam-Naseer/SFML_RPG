#pragma once

class Tile
{
private:

protected:
	sf::RectangleShape shape;

public:
	Tile(float x, float y, float gridSize);
	virtual ~Tile();

	void setPosition(float x, float y);

	void update();
	void render(sf::RenderTarget& target);
};

