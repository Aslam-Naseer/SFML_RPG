#pragma once

#include "Tile.h"
#include "Entity.h"
#include "EnemySpawner.h"

class TileMap
{
private:

	struct Vector2iComparator {
		bool operator()(const sf::Vector2i& left, const sf::Vector2i& right) const {
			if (left.x != right.x)
				return left.x < right.x;
			return left.y < right.y;
		}
	};

	float gridSize;
	sf::Vector2i mapSize;
	int layers;
	sf::RectangleShape mapBorder;

	std::map<sf::Vector2i, std::map<int, EnemySpawner*>, Vector2iComparator> spawners;
	std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;

	sf::Texture tileSheet;
	std::string textureFile;
	sf::RectangleShape collisionBox;
	std::stack<Tile*> deferredRenderStack;

	void initMap(float grid_size, int width, int height, int layers, std::string& texture_file);
	void clearMap();
	bool isValidCoordinate(int x, int y, int layer) const;

public:
	TileMap();
	TileMap(float grid_size, int width, int height, std::string texture_file);
	virtual ~TileMap();

	const sf::Texture& getTileSheet() const;
	const sf::Vector2f getMapSize() const;
	const int getLayerSize(const int x, const int y, const int layer) const;

	sf::Vector2f checkViewBounds(const sf::View& view, sf::Vector2f padding = {0,0}) const;
	sf::Vector2f resolveCollision(const Entity* entity, const float& dt) const;

	void addTile(int x, int y, int layer, short type, bool collision, const sf::IntRect& textureRect);
	void addSpawner(int x, int y, int layer, int enemyType, int spawnCount, float spawnDelay, float spawnRange);
	void removeTile(int x, int y, int layer);
	void removeSpawner(int x, int y, int layer);

	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void update();
	void renderSpawners(sf::RenderTarget& target, sf::Shader* shader);
	void renderDeferred(sf::RenderTarget& target, sf::Shader* shader, bool showCollision = false);
	void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2i& gridPosition, bool showCollision = false);
};

