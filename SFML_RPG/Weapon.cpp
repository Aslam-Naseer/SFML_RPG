#include "stdafx.h"
#include "Weapon.h"


bool Weapon::canAnimate() const
{
	return !timer.isReady() && !animationTimer.isReady();
}

Weapon::Weapon(unsigned lvl):
	Item(lvl, 0), sprite(texture), timer(.35f), animationTimer(.1f)
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

int Weapon::getDamageMin() const
{
	return minDamage;
}

int Weapon::getDamageMax() const
{
	return maxDamage;
}

bool Weapon::isAttackReady() const
{
	if (!timer.consume())
		return false;

	animationTimer.restart();
	return true;
}
