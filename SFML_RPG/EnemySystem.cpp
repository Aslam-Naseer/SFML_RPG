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

void EnemySystem::createEnemy(Type type, float x, float y)
{
	switch (type)
	{
	case EnemySystem::Type::Rat:
		enemies.push_back(new Rat(x, y, this->textures.at("RAT_SHEET")));
		break;
	}
}

void EnemySystem::removeEnemy(int index)
{
	if(index < 0 || index >= static_cast<int>(enemies.size()))
		return;

	delete enemies[index];
	enemies.erase(enemies.begin() + index);
}

void EnemySystem::updateSpawners(sf::Vector2f& playerPosition)
{
	for (auto& spawner : spawners)
	{
		if (spawner->spawnCount < 3 && utils::distance(playerPosition, spawner->shape.getPosition()) < 200)
		{
			createEnemy(Type::Rat, spawner->shape.getPosition().x, spawner->shape.getPosition().y);
			spawner->spawnCount++;
		}
	}
}

void EnemySystem::updateEnemies(const float& dt)
{
	int index = 0;
	for (auto& enemy : enemies)
	{

		if (enemy->isDead())
		{
			enemies.erase(enemies.begin() + index);
			continue;
		}
		
		//enemy->move(dt, -1, 0);
		enemy->update(dt);

		sf::Vector2f resolvedPos = tileMap.resolveCollision(enemy, dt);
		enemy->setPosition(resolvedPos.x, resolvedPos.y);

		index++;
	}
}

void EnemySystem::update(const float& dt, sf::Vector2f playerPosition)
{
	updateSpawners(playerPosition);
	updateEnemies(dt);
}

void EnemySystem::render(sf::RenderTarget& target, sf::Shader* shader)
{
	for(auto& enemy: enemies)
	{
		enemy->render(target, shader);
	}
}