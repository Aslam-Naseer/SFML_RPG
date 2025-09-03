#pragma once

#include "Tile.h"

class TileMap
{
private:
	float gridSize;
	sf::Vector2u mapSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> map;

	sf::Texture tileSheet;

public:
	TileMap(float grid_size);
	virtual ~TileMap();

	const sf::Texture& getTileSheet() const;

	void addTile(unsigned x, unsigned y, unsigned layer, const sf::IntRect& textureRect);
	void removeTile(unsigned x, unsigned y, unsigned layer);

	void update();
	void render(sf::RenderTarget& target);
};

