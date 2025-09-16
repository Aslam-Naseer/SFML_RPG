#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon(unsigned lvl):
	Item(lvl, 0), sprite(texture), timer(.35f)
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
