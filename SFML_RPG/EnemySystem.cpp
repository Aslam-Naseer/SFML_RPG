#include "stdafx.h"
#include "EnemySystem.h"

float EnemySystem::trackPlayer(Enemy* enemy, sf::Vector2f& playerPosition, const float& dt) const
{
	sf::Vector2f enemyMove = playerPosition - enemy->getCenter();
	float dist = utils::length(enemyMove);

	if(dist >= enemy->getAttackRange() && dist <= enemy->getTrackRange())
		enemy->move(dt, 
			(enemyMove.x < 0) ? -1 : (enemyMove.x > 0) ? 1 : 0,
			(enemyMove.y < 0) ? -1 : (enemyMove.y > 0) ? 1 : 0);

	return dist;
}

EnemySystem::EnemySystem(std::map<std::string, sf::Texture>& textures, TileMap& tileMap):
	textures(textures), tileMap(tileMap)
{
}

EnemySystem::~EnemySystem()
{
	for(auto& i : this->enemies)
	{
		delete i;
	}
}

const std::vector<Enemy*> EnemySystem::getEnemies() const
{
	return enemies;
}

void EnemySystem::loadSpawners()
{
	spawners = tileMap.getSpawners();
}

void EnemySystem::createEnemy(Type type, EnemySpawner& spawner)
{
	switch (type)
	{
	case EnemySystem::Type::Rat:
		enemies.push_back(new Rat(this->textures.at("RAT_SHEET"), spawner));
		break;
	}

	spawner.increaseSpawnCount();
}

void EnemySystem::removeEnemy(int index)
{
	if(index < 0 || index >= static_cast<int>(enemies.size()))
		return;

	enemies[index]->getSpawner().decreaseSpawnCount();

	delete enemies[index];
	enemies.erase(enemies.begin() + index);
}

void EnemySystem::updateSpawners(sf::Vector2f& playerPosition)
{
	for (auto& spawner : spawners)
	{
		if (utils::distance(playerPosition, spawner->shape.getPosition()) < spawner->spawnRange 
			&& spawner->canSpawn())
		{
			createEnemy(Type::Rat, *spawner);
		}
	}
}

void EnemySystem::updateEnemies(const float& dt, sf::Vector2f playerPosition)
{
	int index = 0;
	for (auto& enemy : enemies)
	{

		if (enemy->isDead())
		{
			removeEnemy(index);
			continue;
		}
		
		float dist = trackPlayer(enemy, playerPosition, dt);

		sf::Vector2f resolvedPos = tileMap.resolveCollision(enemy, dt);
		enemy->setPosition(resolvedPos.x, resolvedPos.y);

		

		enemy->update(dt);

		index++;
	}
}

void EnemySystem::update(const float& dt, sf::Vector2f playerPosition)
{
	updateSpawners(playerPosition);
	updateEnemies(dt, playerPosition);
}

void EnemySystem::render(sf::RenderTarget& target, sf::Shader* shader)
{
	for(auto& enemy: enemies)
	{
		enemy->render(target, shader);
	}
}