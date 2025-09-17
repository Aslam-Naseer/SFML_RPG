#include "stdafx.h"
#include "Enemy.h"

void Enemy::initHpBar(float maxHp, sf::Vector2f pos)
{
	hpBar = new gui::ProgressBar(pos.x, pos.y, 55.f, 5.f, maxHp, sf::Color(248, 56, 0));
}

void Enemy::calculateExpGain(int level)
{
	expGain = (25 * level) + rand() % (10 * level);
}

void Enemy::updateDamageFlash()
{
	if (damaged && flashTimer.consume())
		sprite.setColor(sf::Color::White);
}


Enemy::Enemy(sf::Texture& texture, EnemySpawner& spawner)
	: Entity(texture), spawner(spawner), despawnTimer(10.f)
{
}

Enemy::~Enemy()
{
}

int Enemy::getExpGain() const
{
	return expGain;
}

float Enemy::getTrackRange() const
{
	return trackRange;
}

float Enemy::getAttackRange() const
{
	return attackRange;
}

void Enemy::startDespawn()
{
	if (despawning)
		return;

	despawning = true;
	despawnTimer.restart();
}

void Enemy::stopDespawn()
{
	despawning = false;
}

bool Enemy::isDespawned() const
{
	return despawning && despawnTimer.isReady();
}


void Enemy::despawn()
{
	spawner.decreaseSpawnCount();
}

bool Enemy::isDead() const
{
	if(!attributeComponent)
		return false;

	return attributeComponent->isDead();
}

void Enemy::loseHp(int hp)
{
	if (!attributeComponent)
		return;

	attributeComponent->loseHp(hp);

	if(hpBar)
	{
		hpBar->setProgress(
			static_cast<float>(attributeComponent->hp),
			static_cast<float>(attributeComponent->hpMax)
		);
	}

	damaged = true;
	sprite.setColor(sf::Color::Red);
	flashTimer.restart();

}

void Enemy::attack(sf::Vector2f target) const
{

}
