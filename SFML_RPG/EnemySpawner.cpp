#include "stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(float x, float y, float gridSize,
	const sf::Texture& tileSheet, const sf::IntRect& textureRect,
	int enemyType, int spawnCount, float spawnDelay, float spawnRange):

	Tile(x,y,gridSize,tileSheet, textureRect, Tile::Type::Spawner, false),
	enemyType(enemyType), spawnCount(spawnCount), spawnDelay(spawnDelay), spawnRange(spawnRange)
{
}

EnemySpawner::~EnemySpawner()
{
}
