#include "stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(float x, float y, float gridSize,
	int enemyType, int maxSpawns, float spawnDelay, float spawnRange):
	enemyType(enemyType), maxSpawns(maxSpawns), spawnDelay(spawnDelay),
	spawnRange(spawnRange), timer(spawnDelay)
{
	shape.setPosition({ x, y });
	shape.setSize({ gridSize, gridSize });
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color(50, 250, 250, 200));
	shape.setOutlineThickness(-1.f);
}

EnemySpawner::~EnemySpawner()
{
}


sf::Vector2f EnemySpawner::getPosition() const
{
	return shape.getPosition();
}


std::string EnemySpawner::toString() const
{
	std::stringstream ss;
	ss << enemyType << " " << maxSpawns << " " 
		<< spawnDelay << " " << spawnRange << " ";

	return ss.str();
}

bool EnemySpawner::canSpawn() const
{
	return (activeSpawns < maxSpawns) && timer.isReady();
}

void EnemySpawner::increaseSpawnCount()
{
	activeSpawns++;
}

void EnemySpawner::decreaseSpawnCount()
{
	if (activeSpawns > 0)
		activeSpawns--;

	timer.restart();
}

void EnemySpawner::update(const float& dt)
{

}


void EnemySpawner::render(sf::RenderTarget& target)
{
	target.draw(shape);
}