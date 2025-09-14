#pragma once

#include "Tile.h"

class EnemySpawner
{
private:
	sf::RectangleShape shape;

	int enemyType;
	int spawnCount;
	float spawnDelay;
	float spawnRange;

public:
	EnemySpawner(float x, float y, float gridSize,
		int enemyType, int spawnCount, float spawnDelay, float spawnRange);
	virtual ~EnemySpawner();

	std::string toString();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

