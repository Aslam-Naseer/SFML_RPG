#include "stdafx.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(int val):
	Item(val), sprite(texture)
{
	type = Type::MeleeWeapon;
}

MeleeWeapon::~MeleeWeapon()
{
}
