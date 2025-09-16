#include "stdafx.h"
#include "Item.h"

Item::Item(unsigned lvl, int val):
	level(lvl), value(val)
{
	type = Type::Default;
}

Item::~Item()
{
}
