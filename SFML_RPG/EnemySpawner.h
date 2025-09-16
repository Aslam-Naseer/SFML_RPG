#pragma once

#include "Tile.h"
#include "KeyTime.h"

class EnemySpawner
{
private:
	int enemyType;
	int maxSpawns;
	float spawnDelay;
	float spawnRange;

	sf::RectangleShape shape;
	int activeSpawns = 0;
	KeyTime timer;

public:
	EnemySpawner(float x, float y, float gridSize,
		int enemyType, int maxSpawns, float spawnDelay, float spawnRange);
	virtual ~EnemySpawner();

	sf::Vector2f getPosition() const;
	std::string toString() const;
	bool canSpawn() const;
	
	void increaseSpawnCount();
	void decreaseSpawnCount();

	void update(const float& dt);
	void render(sf::RenderTarget& target);

	friend class EnemySystem;
};

