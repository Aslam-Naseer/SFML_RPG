#include "stdafx.h"
#include "Item.h"

Item::Item(int val):
	value(val)
{
	type = Type::Default;
}

Item::~Item()
{
}
