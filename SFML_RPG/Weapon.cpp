#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon(int val, int minDmg, int maxDmg, int range):
	Item(val), sprite(texture), minDamage(minDmg), maxDamage(maxDmg),
	range(range), timer(.35f)
{
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

bool Weapon::isAttackReady() const
{
	if (!timer.isReady())
		return false;

	return true;
}
