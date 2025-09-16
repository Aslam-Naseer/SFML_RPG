#include "stdafx.h"
#include "RangedWeapon.h"

void RangedWeapon::generateStats()
{
}

RangedWeapon::RangedWeapon(unsigned lvl):
	Weapon(lvl)
{
	type = Type::RangedWeapon;
}

RangedWeapon::~RangedWeapon()
{
}

void RangedWeapon::generateRandom(unsigned levelMin, unsigned levelMax)
{
	if (levelMin > levelMax)
		std::swap(levelMin, levelMax);

	level = levelMin + rand() % (levelMax - levelMin + 1);
	generateStats();
}
