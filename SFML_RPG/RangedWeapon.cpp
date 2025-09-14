#include "stdafx.h"
#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(int val):
	Item(val)
{
	type = Type::RangedWeapon;
}

RangedWeapon::~RangedWeapon()
{
}
