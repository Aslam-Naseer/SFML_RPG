#include "stdafx.h"
#include "Enemy.h"

void Enemy::initHpBar(float maxHp, sf::Vector2f pos)
{
	hpBar = new gui::ProgressBar(pos.x, pos.y, 55.f, 5.f, maxHp, sf::Color(248, 56, 0));
}

Enemy::Enemy(sf::Texture& texture)
	: Entity(texture)
{
}

Enemy::~Enemy()
{
}

int Enemy::getExpGain() const
{
	return expGain;
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
