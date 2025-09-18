#include "stdafx.h"
#include "AttributeComponent.h"
#include "Player.h"

AttributeComponent::AttributeComponent(int startLevel, int multiplier)
{
    level = startLevel;
    hpMultiplier = multiplier;
    expNext = static_cast<int>(
        50.f * ((pow(level, 3) - 3 * pow(level, 2) + (level * 8)) / 3));

    updateLevel();
    updateStats(true);
}

AttributeComponent::~AttributeComponent()
{

}

std::string AttributeComponent::debugPrint() const
{
    std::stringstream ss;

    ss << "Level: " << level << "\n"
        << "Exp: " << exp << "\n"
        << "Exp Next: " << expNext << "\n"
        << "AttP: " << attributePoints << "\n";

    return ss.str();
}

bool AttributeComponent::isDead() const
{
    return (hp <= 0);
}

void AttributeComponent::gainExp(const int expGain)
{
    exp += expGain;
    updateLevel();
}

void AttributeComponent::loseExp(int expLose)
{
    exp -= expLose;
    exp = std::max(0, exp);
}


void AttributeComponent::gainHp(int hpGain)
{
    hp += hpGain;
    hp = std::min(hp, hpMax);
}

void AttributeComponent::loseHp(int hpLose)
{
    hp -= hpLose;
    hp = std::max(0, hp);
}


void AttributeComponent::updateStats(const bool reset)
{
    //hpMax =     vitality * 7 + strength / 2 + intelligence / 5;
    //damageMin = strength * 2 + strength / 4 + intelligence / 5;
    //damageMax = strength * 2 + strength / 2 + intelligence / 5;
    //accuracy =  dexterity * 5 + dexterity / 2 + intelligence / 5;
    //defence =   agility * 2 + agility / 4 + intelligence / 5;
    //luck =      intelligence * 2 + intelligence / 5;

    hpMax = level * hpMultiplier;
    damageMin = level * 2;
    damageMax = level * 3;


    if (reset) hp = hpMax;
}

void AttributeComponent::updateLevel()
{
    while (exp >= expNext)
    {
        level++;
        attributePoints++;
        exp -= expNext;

        expNext = static_cast<int>(
            50.f * ((pow(level, 3) - 3 * pow(level, 2) + (level * 8)) / 3));

        updateStats(true);
    }
}

void AttributeComponent::update()
{
    updateLevel();
}