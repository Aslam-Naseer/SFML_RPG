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
	std::string textureFile;

	void initMap(float grid_size, unsigned width, unsigned height, unsigned layers, std::string& texture_file);
	void clearMap();

public:
	TileMap();
	TileMap(float grid_size, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();

	const sf::Texture& getTileSheet() const;

	void addTile(unsigned x, unsigned y, unsigned layer, const sf::IntRect& textureRect);
	void removeTile(unsigned x, unsigned y, unsigned layer);

	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void update();
	void render(sf::RenderTarget& target);
};

