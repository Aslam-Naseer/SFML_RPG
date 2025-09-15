#include "stdafx.h"
#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(int val, int minDmg, int maxDmg, int range):
	Weapon(val, minDmg, maxDmg, range)
{
	type = Type::RangedWeapon;
}

RangedWeapon::~RangedWeapon()
{
}
