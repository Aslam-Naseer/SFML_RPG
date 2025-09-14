#pragma once

class Item
{
public:
	enum class Type {
		Default,
		MeleeWeapon,
		RangedWeapon
	};

protected:
	Type type;
	int value;

public:
	Item(int val);
	virtual ~Item();

	virtual Item* clone() = 0;
};

