#include "stdafx.h"
#include "EnemySystem.h"

float EnemySystem::trackPlayer(Enemy* enemy, sf::Vector2f& playerPosition, const float& dt) const
{
	sf::Vector2f enemyMove = playerPosition - enemy->getCenter();
	float dist = utils::length(enemyMove);

	if (dist > enemy->getTrackRange())
		return dist;

	if (dist > enemy->getAttackRange() + 20.f)
	{
		enemy->move(dt, enemyMove.x, enemyMove.y);
	}

	else if (dist > enemy->getAttackRange())
	{
		auto [vx, vy] = enemy->getVelocity();
		enemy->move(dt, vx, vy );
	}

	else
	{
		enemy->move(dt, enemyMove.x * -1, enemyMove.y * -1);
	}

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

int EnemySystem::getTotalDamage()
{
	int temp = totalDamage;
	totalDamage = 0;
	return temp;
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

	enemies[index]->despawn();

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

		if (enemy->isDead() || enemy->isDespawned())
		{
			removeEnemy(index);
			continue;
		}
		
		float dist = trackPlayer(enemy, playerPosition, dt);

		sf::Vector2f resolvedPos = tileMap.resolveCollision(enemy, dt);
		enemy->setPosition(resolvedPos.x, resolvedPos.y);

		if (dist > despawnRange)
			enemy->startDespawn();
		else
			enemy->stopDespawn();

		if (dist <= enemy->getAttackRange())
			totalDamage += enemy->attack();
		

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