#include "stdafx.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(int val, int minDmg, int maxDmg, int range):
	Weapon(val, minDmg, maxDmg, range)
{
	type = Type::MeleeWeapon;
}

MeleeWeapon::~MeleeWeapon()
{
}
