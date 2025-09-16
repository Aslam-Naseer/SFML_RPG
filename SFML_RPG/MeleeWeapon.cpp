#include "stdafx.h"
#include "MeleeWeapon.h"

void MeleeWeapon::generateStats()
{
	if (level == 0) return;

	minDamage = level * (rand() % 2 + 1);
	maxDamage = level * (rand() % 2 + 1) + minDamage;

	range = level + rand() % 10 + 50;
	value = level + minDamage + maxDamage + range + (rand() % level * 10);

	std::cout << "===== Weapon Stats ======" << std::endl;
	std::cout << "Level:     " << level << std::endl;
	std::cout << "Damage:    " << minDamage << " - " << maxDamage << std::endl;
	std::cout << "Range:     " << range << std::endl;
	std::cout << "Value:     " << value << " gold" << std::endl;
	std::cout << "=========================" << std::endl;
}


MeleeWeapon::MeleeWeapon(unsigned lvl):
	Weapon(lvl)
{
	type = Type::MeleeWeapon;
	generateStats();
}

MeleeWeapon::~MeleeWeapon()
{
}

void MeleeWeapon::generateRandom(unsigned levelMin, unsigned levelMax)
{
	if (levelMin > levelMax)
		std::swap(levelMin, levelMax);

	level = levelMin + rand() % (levelMax - levelMin + 1);
	generateStats();
}
