#pragma once

#include "Item.h"

class RangedWeapon :
    public Item
{
private:

public:
    RangedWeapon(int val);
    virtual ~RangedWeapon();

    virtual RangedWeapon* clone() = 0;
};

