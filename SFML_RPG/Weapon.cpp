#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon(int val, int minDmg, int maxDmg, int range):
	Item(val), sprite(texture), minDamage(minDmg), maxDamage(maxDmg), range(range)
{
	attackCooldown = sf::seconds(1.f);
	attackTimer.restart();
}

Weapon::~Weapon()
{
}

int Weapon::getDamage() const
{
	return minDamage + rand()%(maxDamage - minDamage + 1);
}

int Weapon::getRange() const
{
	return range;
}

bool Weapon::isAttackReady()
{
	if (attackTimer.getElapsedTime() < attackCooldown)
		return false;

	attackTimer.restart();
	return true;
}
