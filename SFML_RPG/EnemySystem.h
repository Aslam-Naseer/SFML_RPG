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
	TileMap& tileMap;

public:
	EnemySystem(std::map<std::string, sf::Texture>& textures, TileMap& tilemap);
	virtual ~EnemySystem();

	const std::vector<Enemy*> getEnemies() const;
	void setSpawners(const std::vector<EnemySpawner*>& spawners);

	void createEnemy(Type type, float x, float y);
	void removeEnemy(int index);

	void updateSpawners(sf::Vector2f& playerPosition);
	void updateEnemies(const float& dt);

	void update(const float& dt, sf::Vector2f playerPosition);
	void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);

};

