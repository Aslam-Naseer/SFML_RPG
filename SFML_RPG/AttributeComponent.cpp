#include "stdafx.h"
#include "AttributeComponent.h"
#include "Player.h"

AttributeComponent::AttributeComponent(unsigned startLevel)
{
    level = startLevel;
    expNext = static_cast<unsigned>(
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

void AttributeComponent::gainExp(const unsigned expGain)
{
    exp += expGain;
    updateLevel();
}

void AttributeComponent::updateStats(const bool reset)
{
    hpMax =     vitality * 7 + strength / 2 + intelligence / 5;
    damageMin = strength * 2 + strength / 4 + intelligence / 5;
    damageMax = strength * 2 + strength / 2 + intelligence / 5;
    accuracy =  dexterity * 5 + dexterity / 2 + intelligence / 5;
    defence =   agility * 2 + agility / 4 + intelligence / 5;
    luck =      intelligence * 2 + intelligence / 5;

    if (reset) hp = hpMax;
}

void AttributeComponent::updateLevel()
{
    if (exp >= expNext)
    {
        level++;
        attributePoints++;
        exp -= expNext;

        expNext = static_cast<unsigned>(
            50.f * ((pow(level, 3) - 3 * pow(level, 2) + (level * 8)) / 3));
    }
}

void AttributeComponent::update()
{
    updateLevel();
}