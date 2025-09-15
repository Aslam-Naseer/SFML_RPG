#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(sf::Texture& texture)
	: Entity(texture)
{
}

Enemy::~Enemy()
{
}

int Enemy::getExpGain() const
{
	return 0;
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
}
