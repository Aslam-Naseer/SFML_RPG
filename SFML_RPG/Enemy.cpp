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

Enemy::Enemy(sf::Texture& texture, EnemySpawner& spawner)
	: Entity(texture), spawner(spawner)
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

EnemySpawner& Enemy::getSpawner()
{
	return spawner;
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
}

void Enemy::attack(sf::Vector2f target) const
{

}
