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
	unsigned level;
	int value;

public:
	Item(unsigned lvl, int val);
	virtual ~Item();

	unsigned getLevel() const;
	int getValue() const;

	virtual Item* clone() = 0;
};

