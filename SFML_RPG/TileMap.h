#pragma once

#include "Tile.h"
#include "Entity.h"

class TileMap
{
private:
	float gridSize;
	sf::Vector2i mapSize;
	int layers;
	sf::RectangleShape mapBorder;

	std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;
	sf::Texture tileSheet;
	std::string textureFile;
	sf::RectangleShape collisionBox;
	std::stack<Tile*> deferredRenderStack;

	void initMap(float grid_size, int width, int height, int layers, std::string& texture_file);
	void clearMap();

public:
	TileMap();
	TileMap(float grid_size, int width, int height, std::string texture_file);
	virtual ~TileMap();

	const sf::Texture& getTileSheet() const;
	bool isWithinBounds(float x, float y) const;
	const sf::Vector2f getMapSize() const;
	const int getLayerSize(const int x, const int y, const int layer) const;

	sf::Vector2f resolveCollision(const Entity* entity, const float& dt) const;
	void addTile(int x, int y, int layer, short type, bool collision, const sf::IntRect& textureRect);
	void removeTile(int x, int y, int layer);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void update();
	void renderDeferred(sf::RenderTarget& target, sf::Shader* shader);
	void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2i& gridPosition, bool showCollision = false);
};

