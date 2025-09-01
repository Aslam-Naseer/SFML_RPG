#pragma once

#include "Tile.h"

class TileMap
{
private:
	float gridSize;
	sf::Vector2u mapSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile>>> map;

public:
	TileMap();
	virtual ~TileMap();

	void update();
	void render(sf::RenderTarget& target);
};

