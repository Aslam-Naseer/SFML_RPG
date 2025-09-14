#include "stdafx.h"
#include "Bow.h"

Bow::Bow():
	RangedWeapon(150)
{
}

Bow::~Bow()
{
}

Bow* Bow::clone()
{
	return new Bow(*this);
}
