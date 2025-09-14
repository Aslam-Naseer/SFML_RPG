#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::map<std::string, sf::Texture>& textures):
	textures(textures)
{
}

EnemySystem::~EnemySystem()
{
	for(auto& i : this->enemies)
	{
		delete i;
	}
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

void EnemySystem::update(const float& dt, const sf::Vector2f playerPosition)
{
	for(auto& spawner: spawners)
	{
		if(spawner->spawnCount < 5 &&
			std::abs(playerPosition.x - spawner->shape.getPosition().x) < 250 &&
			std::abs(playerPosition.y - spawner->shape.getPosition().y) < 250)
		{
			createEnemy(Type::Rat, spawner->shape.getPosition().x, spawner->shape.getPosition().y);
			spawner->spawnCount++;
		}
	}


	for(auto& Enemy: enemies)
		Enemy->update(dt);

}

void EnemySystem::render(sf::RenderTarget& target, sf::Shader* shader)
{
	for(auto& enemy: enemies)
	{
		enemy->render(target, shader);
	}
}