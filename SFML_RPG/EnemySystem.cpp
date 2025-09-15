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

void EnemySystem::update(const float& dt, const Player& player)
{
	for(auto& spawner: spawners)
	{
		if(spawner->spawnCount < 3 && utils::distance(player.getPosition(), spawner->shape.getPosition()) < 200)
		{
			createEnemy(Type::Rat, spawner->shape.getPosition().x, spawner->shape.getPosition().y);
			spawner->spawnCount++;
			std::cout << " Bro spawned lmao \n";
		}
	}


	int index = 0;
	for(auto& enemy: enemies)
	{
		//enemy->move(dt, -1, 0);
		enemy->update(dt);

		sf::Vector2f resolvedPos = tileMap.resolveCollision(enemy, dt);
		enemy->setPosition(resolvedPos.x, resolvedPos.y);

		if (player.isAttacking()
			&& utils::distance(player.getCenter(), enemy->getCenter()) < player.getWeapon()->getRange()
			&& player.getWeapon()->isAttackReady())
		{
			int dmg = player.getWeapon()->getDamage();
			enemy->loseHp(dmg);

			std::cout << "Rat: " << index << " -> " << dmg << "\t";

			// DANGEROUS - Change later
			if (enemy->isDead())
			{	
				std::cout << "\n" << "Bro at " << index << " died lmao" << "\n";
				enemies.erase(enemies.begin() + index);
				index--;
			}
		}

		index++;
	}

}

void EnemySystem::render(sf::RenderTarget& target, sf::Shader* shader)
{
	for(auto& enemy: enemies)
	{
		enemy->render(target, shader);
	}
}