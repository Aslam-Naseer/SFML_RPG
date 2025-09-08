#pragma once

class AttributeComponent
{
public:
	//Leveling
	unsigned level = 1;
	unsigned exp = 0;
	unsigned expNext = 0;
	unsigned attributePoints = 2;

	//Attributes
	int vitality = 1;
	int strength = 1;
	int dexterity = 1;
	int agility = 1;
	int intelligence = 1;

	//Stats
	int hp = 0;
	int hpMax = 0;
	int damageMin = 0;
	int damageMax = 0;
	int accuracy = 0;
	int defence = 0;
	int luck = 0;

	AttributeComponent(unsigned startLevel);
	~AttributeComponent();

	std::string debugPrint() const;
	void gainExp(const unsigned exp);

	void updateStats(const bool reset);
	void updateLevel();

	void update();
};