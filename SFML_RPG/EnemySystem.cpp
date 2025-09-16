#include "stdafx.h"
#include "EnemySystem.h"

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

void EnemySystem::setSpawners(const std::vector<EnemySpawner*>& spawners)
{
	this->spawners = spawners;
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
		
		sf::Vector2f enemyMove = playerPosition - enemy->getPosition();
		enemy->move(dt, 
			(enemyMove.x < 0) ? -1 : (enemyMove.x > 0) ? 1 : 0,
			(enemyMove.y < 0) ? -1 : (enemyMove.y > 0) ? 1 : 0);


		enemy->update(dt);

		sf::Vector2f resolvedPos = tileMap.resolveCollision(enemy, dt);
		enemy->setPosition(resolvedPos.x, resolvedPos.y);

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