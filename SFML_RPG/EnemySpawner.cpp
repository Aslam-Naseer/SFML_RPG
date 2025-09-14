#include "stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(float x, float y, float gridSize,
	int enemyType, int spawnCount, float spawnDelay, float spawnRange):
	enemyType(enemyType), spawnCount(spawnCount), spawnDelay(spawnDelay), spawnRange(spawnRange)
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

std::string EnemySpawner::toString()
{
	std::stringstream ss;
	ss << enemyType << " " << spawnCount << " " 
		<< spawnDelay << " " << spawnRange << " ";

	return ss.str();
}

void EnemySpawner::update(const float& dt)
{

}


void EnemySpawner::render(sf::RenderTarget& target)
{
	target.draw(shape);
}