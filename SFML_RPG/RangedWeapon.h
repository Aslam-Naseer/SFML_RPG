#pragma once

#include "Weapon.h"

class RangedWeapon :
    public Weapon
{
private:

public:
    RangedWeapon(int val, int minDmg, int maxDmg, int range);
    virtual ~RangedWeapon();

    virtual RangedWeapon* clone() = 0;
};

