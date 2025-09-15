#pragma once

class AttributeComponent
{
public:
	//Leveling
	int level = 1;
	int exp = 0;
	int expNext = 0;
	int attributePoints = 2;

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

	AttributeComponent(int startLevel);
	~AttributeComponent();

	std::string debugPrint() const;
	bool isDead() const;

	void gainExp(const int expGain);
	void loseExp(const int expLose);
	void gainHp(const int hpGain);
	void loseHp(const int hpLose);

	void updateStats(const bool reset);
	void updateLevel();

	void update();
};