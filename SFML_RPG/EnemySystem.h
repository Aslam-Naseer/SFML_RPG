#pragma once

#include "Rat.h"
#include "EnemySpawner.h"
#include "TileMap.h"
#include "Player.h"

class EnemySystem
{
public:
	enum class Type
	{
		Rat
	};

private:
	std::map<std::string, sf::Texture>& textures;
	std::vector<EnemySpawner*> spawners;
	std::vector<Enemy*> enemies;
	
	const TileMap& tileMap;
	float despawnRange = 1500.f;
	float totalDamage = 0.f;

	float trackPlayer(Enemy* enemy, sf::Vector2f& playerPosition, const float& dt) const;

public:
	EnemySystem(std::map<std::string, sf::Texture>& textures, TileMap& tilemap);
	virtual ~EnemySystem();

	const std::vector<Enemy*> getEnemies() const;
	float getTotalDamage();
	void loadSpawners();

	void createEnemy(Type type, EnemySpawner& spawner);
	void removeEnemy(int index);

	void updateSpawners(sf::Vector2f& playerPosition);
	void updateEnemies(const float& dt, sf::Vector2f playerPosition);

	void update(const float& dt, sf::Vector2f playerPosition);
	void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);

};

