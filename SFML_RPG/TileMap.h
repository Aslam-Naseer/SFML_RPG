#pragma once

#include "Tile.h"
#include "Entity.h"

class TileMap
{
private:
	float gridSize;
	sf::Vector2u mapSize;
	unsigned layers;
	sf::RectangleShape mapBorder;

	std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;
	sf::Texture tileSheet;
	std::string textureFile;
	sf::RectangleShape collisionBox;

	void initMap(float grid_size, unsigned width, unsigned height, unsigned layers, std::string& texture_file);
	void clearMap();

public:
	TileMap();
	TileMap(float grid_size, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();

	const sf::Texture& getTileSheet() const;
	bool isWithinBounds(float x, float y) const;
	const sf::Vector2f getMapSize() const;
	const int getLayerSize(const int x, const int y, const int layer) const;

	sf::Vector2f resolveCollision(const Entity* entity, const float& dt) const;
	void addTile(unsigned x, unsigned y, unsigned layer, short type, bool collision, const sf::IntRect& textureRect);
	void removeTile(unsigned x, unsigned y, unsigned layer);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void update();
	void render(sf::RenderTarget& target, const sf::Vector2i& gridPosition);
};

