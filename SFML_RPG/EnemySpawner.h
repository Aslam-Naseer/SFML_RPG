#pragma once

#include "Tile.h"

class EnemySpawner:
	public Tile
{
private:
	int enemyType;
	int spawnCount;
	float spawnDelay;
	float spawnRange;
public:
	EnemySpawner(float x, float y, float gridSize, 
		const sf::Texture& tileSheet, const sf::IntRect& textureRect,
		int enemyType, int spawnCount, float spawnDelay, float spawnRange);
	virtual ~EnemySpawner();
};

