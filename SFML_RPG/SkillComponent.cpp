#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::Skill::Skill(Skills type):
	type(type)
{
}

SkillComponent::Skill::~Skill()
{
}

void SkillComponent::Skill::gainExp(const int expGain)
{
	exp += expGain;
	updateLevel(true);
}

void SkillComponent::Skill::loseExp(const int expLose)
{ 
	exp -= expLose;
	updateLevel(false);
}

void SkillComponent::Skill::updateLevel(bool levelUp)
{
	if (levelUp)
	{
		while (level < levelCap && exp > expNext)
		{
			level++;
			exp -= expNext;
			expNext = level * 100;
		}
	}

	else
	{
		while (level > 0 && exp < 0)
		{
			level--;
			exp += expNext;
			expNext = level * 100;
		}
	}
}

void SkillComponent::Skill::update()
{

}

SkillComponent::SkillComponent()
{
	skills.push_back(Skill(Skills::Constitution));
	skills.push_back(Skill(Skills::MeleeCombat));
	skills.push_back(Skill(Skills::RangedCombat));
	skills.push_back(Skill(Skills::Endurance));
}

SkillComponent::~SkillComponent()
{
}

const int SkillComponent::getSkill(const Skills skill) const
{
	int index = static_cast<int>(skill);
	if (skills.empty() || index < 0 || index >= skills.size())
		throw std::runtime_error("ERROR::SKILLCOMPONENT::GETSKILL::SKILL_DOES_NOT_EXIST");

	return skills[index].level;
}

void SkillComponent::gainExp(const Skills skill, const int exp)
{
	int index = static_cast<int>(skill);
	if (skills.empty() || index < 0 || index >= skills.size())
		throw std::runtime_error("ERROR::SKILLCOMPONENT::GETSKILL::SKILL_DOES_NOT_EXIST");

	skills[index].gainExp(exp);
}
